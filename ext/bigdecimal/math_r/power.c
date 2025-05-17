/*******************************************************************************
	power.c -- Power functions

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
 *  d = BigMathR::Power.integer_power(Math::E, 2*2, Float::MAX_10_EXP).round(Float::DIG)
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
__impl_power_integer_power(VALUE unused_obj, VALUE x, VALUE n, VALUE exp)
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
 * Computes square root of +x+.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::PowerRoot.sqrt(2, 20)
 *  #=> 0.14142135623730950488e1
 * @since 0.1.0
 */
static VALUE
__impl_power_sqrt(VALUE unused_obj, VALUE x, VALUE prec)
{
	VALUE y;
	y = rb_bigmath_sqrt(x, prec);
	return rb_num_round(y, prec);
}

/**
 * Computes complex square root of +z+.
 * 
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 * @example
 *  BigMathR::PowerRoot.csqrt(-1, 20) == Complex::I
 *  #=> true
 * @since 0.1.0
 */
static VALUE
__impl_power_csqrt(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
        return csqrt_formula(z, prec);
}

/**
 * Computes real-valued cubic root of +x+.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::PowerRoot.cuberoot(-2, 20)
 *  #=> -0.12599210498948731648e1
 * @since 0.1.0
 */
static VALUE
__impl_power_cuberoot(VALUE unused_obj, VALUE x, VALUE prec)
{
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return cuberoot_newton(x, prec);
}


/**
 * Computes complex cubic root of +z+.
 * 
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 * @example
 *  BigMathR::PowerRoot.ccbrt(-2, 20)
 *  #=> (0.6299605249474365824e0+0.10911236359717214036e1i)
 * @since 0.1.0
 */
static VALUE
__impl_power_ccbrt(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
        return ccbrt_formula(z, prec);
}

/**
 *  Document-module:  BigMathR::Power
 *  
 *  A module that provides the power functions. 
 *  It is used internally.
 *  <br>
 *  == Synopsis
 *  The function names defined are the same as those in the C/C++ standard.
 *  <br>
 *  - Square root:          +:sqrt+ +:csqrt+ <br>
 *  - Cubic root:           +:ccbrt+ <br>
 *  Follow, the name defined in C/C++ standard though, the function names are different.
 *  <br>
 *  - Cubic root:           +:cuberoot+ ( +cbrt()+ for C/C++ ) <br>
 *  Reference::
 *  C-gengo ni yoru hyoujun algorithm jiten (Japanese) - Haruhiko Okumura (Gijutu Hyouron-sha)
 */
void
InitVM_Power(void)
{
	rb_define_module_function(rb_mPower, "integer_power", __impl_power_integer_power, 3);

	rb_define_module_function(rb_mPower, "sqrt", __impl_power_sqrt, 2);
	rb_define_module_function(rb_mPower, "csqrt", __impl_power_csqrt, 2);
	rb_define_module_function(rb_mPower, "cuberoot", __impl_power_cuberoot, 2);
	rb_define_module_function(rb_mPower, "ccbrt", __impl_power_ccbrt, 2);
}
