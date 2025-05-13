/*******************************************************************************
	edf.c -- Exponential Decomposition Formula

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"
#include "decl.h"

/**
 * Computes the Integer +n+ power of +x+.
 * <br>
 * Notice that the precision parameter of this function is a decimal exponent.
 * <br>
 * Because the exponential value means the maximum digit, 
 * the value retains the significant digits.
 * <br>
 * Therefore, if the solution exceeds the range of significant digits, 
 * it returns infinity at the upper bound and 0 at the lower bound.
 * <br>
 * For example, the solution of 2**-100 with an exponential value of 20 is 0.
 * @example
 *  d = BigMathR::EDF.integer_power(Math::E, 2*2, Float::MAX_10_EXP).round(Float::DIG)
 *  #=> 0.5459815003314423e2
 *  BigDecimal(((d - 1)/(d + 1)), Float::DIG)
 *  #=> 0.964027580075817e0
 *  Math.tanh(2)
 *  #=> 0.9640275800758169
 * @param x [Numeric] Numerical argument
 * @param n [Integer] Integer power
 * @param exp [Integer] Maximum of the decimal exponent for solution
 * @return [BigDecimal] Solution for +x**n+
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @since 0.1.0
 */
static VALUE
__impl_edf_integer_power(VALUE unused_obj, VALUE x, VALUE n, VALUE exp)
{
	VALUE y;
	
	rb_check_precise(exp);
	x = rb_num_canonicalize(x, exp, ARG_REAL, ARG_RAWVALUE);
	if (!(TYPE(n) == T_FIXNUM || TYPE(n) == T_BIGNUM))
		rb_raise(rb_eTypeError, "right-hand side must be an Integer");
	
	y = ipow_edf(x, n, exp);
	
	return y;
}

/**
 * Exponentially-decompose into the form of
 * [a ** x.floor, x % 1].
 * <br>
 * Where `escalb' mean "Exponential SCALe Binary".
 * <br>
 * @param a [Numeric] Base of exponential decomposition
 * @param x [Numeric] X-axis
 * @param prec [Integer] Arbitrary precision
 * @return [Array] Decomposed values as [a ** x.floor, x % 1]
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::EDF.escalb(BigMathR.E(20), 2, 20)
 *  #=> [0.73890560989306502274e1, 0.0]
 * @since 0.1.0
 */
static VALUE
__impl_edf_escalb(VALUE unused_obj, VALUE a, VALUE x, VALUE prec)
{
	VALUE exp = Qundef, fra = Qundef;
	rb_bigmath_escalb(a, x, prec, &exp, &fra);
	if (exp == Qundef || fra == Qundef)
		rb_raise(rb_eRuntimeError, "no solution");
	exp = rb_num_round(exp, prec);
	fra = rb_num_round(fra, prec);
	return rb_assoc_new(exp, fra);
}


/**
 * Calculate the exponential function of +x+ with base +t+.
 * 
 * @param x [Numeric] Numerical Argument. Domain as 0<=x<1.
 * @param t [Numeric] Base of +x+. 1 = e, log2 = 2
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Fraction number
 * @example
 *  BigMathR::EDF.expxt(0.5, BigMathR.LOG2(20), 20)
 *  #=> 0.14142135623730950488e1
 * @since 0.1.0
 */
static VALUE
__impl_edf_expxt(VALUE unused_obj, VALUE x, VALUE t, VALUE prec)
{
	return rb_bigmath_expxt(x, t, prec);
}

/**
 * Based on the radix complementation method, exponentially-decompose +x+ on radix 2.
 * <br>
 * It behaves the same as frexp() in C, 
 * except that the value range is 1 leq y lt 2 with its exponent.
 * <br>
 * If +x+ is not positive finite except 0, then it is inherently undefined. 
 * However, if +x+ is negative finite, it will return a value range of -2 lt +y+ leq -1.
 * @param x [Numeric] Numerical argument
 * @return [Array] Decomposed values as [fraction, exponent]
 * @example
 *  fra, exp = BigMathR::EDF.rcm2(3)
 *  #=> [(3/2), 1]
 *  fra = BigMathR::EDF.logxt(fra, 2, 20)
 *  #=> 0.58496250072115618145e0
 *  log2_3 = exp + fra
 *  #=> 0.158496250072115618145e1
 *  Math.log2(3) == log2_3.to_f
 *  #=> true
 * @since 0.1.0
 */
static VALUE
__impl_edf_rcm2(VALUE unused_obj, VALUE x)
{
	VALUE exp, fra;
	fra = rcm2_edf(x, &exp);
	return rb_assoc_new(fra, exp);
}


/**
 * Based on the radix complementation method, exponentially-decompose +x+ on radix 10.
 * <br>
 * It behaves the same as frexp() in C,
 * except that the radix is 10 and the value range is 1 leq y lt 10.
 * <br>
 * If +x+ is not positive finite except 0, then it is inherently undefined. 
 * However, if +x+ is negative finite, it will return a value range of -10 lt +y+ leq -1.
 * @param x [Numeric] Numerical argument
 * @return [Array] Decomposed values as [fraction, exponent]
 * @example
 *  fra, exp = BigMathR::EDF.rcm10(3)
 *  #=> [(3/1), 0]
 *  fra = BigMathR::EDF.logxt(fra, 10, 20)
 *  #=> 0.4771212547196624373e0
 *  log10_3 = exp + fra
 *  #=> 0.4771212547196624373e0
 *  Math.log10(3) == log10_3.to_f
 *  #=> true
 * @since 0.1.0
 */
static VALUE
__impl_edf_rcm10(VALUE unused_obj, VALUE x)
{
	VALUE exp, fra;
	fra = rcm10_edf(x, &exp);
	return rb_assoc_new(fra, exp);
}


/**
 * Computes fraction of +x+ with its complement +t+ in the exponential decomposition.
 * <br>
 * Complement is equal to the base +x+, and the decomposition varies depending on the value given.
 * @example
 *  BigMathR::EDF.logxt(2, 10, 20) #=> 0.30102999566398119521e0
 *  BigMathR::EDF.logxt(2, 2, 20) #=> 0.1e1
 *  BigMathR::EDF.logxt(2, Math::E, Float::DIG) #=> 0.693147180559945e0
 * @param x [Numeric] Numerical Argument. Domain as 1<=x<=t.
 * @param t [Numeric] Complement of +x+. e = ln(x), 2 = log_2(x), 10 = log_10(x)
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Solution of log_t(x)
 * @raise [FloatDomainError] Numerical arguments are out of range
 * @since 0.1.0
 * @see Programming in Oberon - Niklaus Wirth
 */
static VALUE
__impl_edf_logxt(VALUE unused_obj, VALUE x, VALUE t, VALUE prec)
{
	rb_check_precise(prec);
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	if (rb_num_notequal_p(x, x) ||
	    rb_num_negative_p(x) || 
	    NUM2INT(rb_num_cmpeql(INT2FIX(1), x)) == 1 || 
	    NUM2INT(rb_num_cmpeql(x, t)) != -1)
	{
		if (rb_num_equal_p(x, t))
			return BIG_ONE;
		rb_raise(rb_eFloatDomainError, "Numerical arguments are out of range: (1 <= x <= t)");
	}
	t = rb_num_canonicalize(t, prec, ARG_REAL, ARG_RAWVALUE);
	x = logxt_edf(x, t, prec);
	return rb_num_round(x, prec);
}



/**
 *  Document-module:  BigMathR::EDF
 *  
 *  A module that treats the exponential decomposition formula.
 *  It is used internally.
 *  <br>
 *  This formula was discovered by the author shortly afterwards. It will be proven in time.
 *  <br>
 *  == Synopsis:
 *  The function names defined are the same as those in the C/C++ standard.
 *  <br>
 *  Exponential function:     +exp()+ <br>
 *  Base-2 (binary) exponent: +exp2()+ <br>
 *  
 *  Reference::
 *  {https://github.com/tribusonz-2/edf Exponential Decomposition Formula}
 */
void
InitVM_EDF(void)
{
	rb_define_module_function(rb_mEDF, "integer_power", __impl_edf_integer_power, 3);
	rb_define_module_function(rb_mEDF, "escalb", __impl_edf_escalb, 3);
	rb_define_module_function(rb_mEDF, "expxt", __impl_edf_expxt, 3);

	rb_define_module_function(rb_mEDF, "rcm2", __impl_edf_rcm2, 1);
	rb_define_module_function(rb_mEDF, "rcm10", __impl_edf_rcm10, 1);

	rb_define_module_function(rb_mEDF, "logxt", __impl_edf_logxt, 3);
}
