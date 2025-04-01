/*******************************************************************************
	edf.c -- Exponential Decomposition Formula

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"

#define USE_MERCATOR 0

/**
 * 
 *  Implementation is equivalent as follow:
 *  ```Ruby
 *  def intpower(x, n, exp)
 *    eps = 10 ** exp
 *    if !n.finite?
 *      case n.infinite?
 *      when 1
 *        return BigDecimal::INFINITY
 *      when -1
 *        return Rational(0)
 *      when nil
 *        return BigDecimal::NAN
 *      end
 *    end
 *    x = Rational(x)
 *    abs_n = n.abs;  r = 1;
 *    while (abs_n != 0)
 *      if (abs_n & 1 == 1)
 *        r *= x
 *        if r > eps
 *          r = BigDecimal::INFINITY
 *        end
 *      end
 *      break if r.infinite?
 *      x *= x;  abs_n >>= 1;
 *    end
 *    (n >= 0) ? r : 1 / r
 *  end
 *  ```
 * 
 */
static VALUE
rb_bigmath_intpower(VALUE x, VALUE n, VALUE exp)
{
	const ID mult = rb_intern("mult");
	const ID exponent = rb_intern("exponent");
	const ID r_shift = rb_intern(">>");
	const ID geq = rb_intern(">=");
	VALUE abs_n = Qundef, r = Qundef;
	if (!rb_num_finite_p(x))
		return BIG_NAN;
	x = rb_num_canonicalize(x, exp, ARG_REAL, ARG_RAWVALUE);
	abs_n = n;
	if (rb_num_negative_p(n))  abs_n = rb_num_uminus(abs_n); // abs()
	r = BIG_ONE;
	while (rb_num_nonzero_p(abs_n))
	{
		if (RTEST(NUM2INT(rb_num_coerce_bit(abs_n, INT2FIX(1), '&'))))
		{
			r = rb_funcall(r, mult, 2, x, exp);
			if (RTEST(rb_num_coerce_cmp(rb_funcall(
			r, exponent, 0), exp, '>')))
				r = BIG_INF;
		}
		if (rb_num_infinite_p(r))
			break;
		x = rb_funcall(x, mult, 2, x, exp);
		abs_n = rb_num_coerce_bit(abs_n, INT2FIX(1), r_shift);
	}
	return RTEST(rb_num_coerce_cmp(n, INT2FIX(0), geq)) ?
		r : rb_funcall1(INT2FIX(1), '/', r);
}


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
edf_integer_power(VALUE unused_obj, VALUE x, VALUE n, VALUE exp)
{
	VALUE y;
	
	rb_check_precise(exp);
	x = rb_num_canonicalize(x, exp, ARG_REAL, ARG_RAWVALUE);
	if (!(TYPE(n) == T_FIXNUM || TYPE(n) == T_BIGNUM))
		rb_raise(rb_eTypeError, "right-hand side must be an Integer");
	
	y = rb_bigmath_intpower(x, n, exp);
	
	return y;
}


/**
 *
 *  ```Ruby
 *  def escalb(a, x, prec)
 *    raise RangeError, "parameter a must be positive finite"\
 *      unless a.finite? and a.positive?
 *    exp = 0; fra = 0
 *    case x
 *    when Integer
 *      exp = x
 *    when Float
 *      if x.nan? or x.infinite?
 *        exp = x
 *      else
 *        exp = x.floor; fra = x % 1;
 *      end
 *    when Rational
 *      exp = x.floor; fra = x % 1;
 *    when Complex
 *      raise TypeError, "no solution for Complex"
 *    when BigDecimal
 *      if x.nan? or x.infinite?
 *        exp = x
 *      else
 *        exp = x.fix.to_i
 *        if x.negative? and exp != x
 *          exp = exp.pred
 *        end
 *        unless exp == x
 *          fra = x.frac
 *          if fra.negative?
 *            fra = 1 + fra
 *          end
 *        end
 *      end
 *    else
 *      raise TypeError, "unknown numeric class"
 *    end
 *    [intpower(a, exp, prec), fra]
 *  end
 *  ```
 */
static void
rb_bigmath_escalb(VALUE a, VALUE x, VALUE prec, VALUE *exp, VALUE *fra)
{
	const ID fix = rb_intern("fix");
	const ID frac = rb_intern("frac");
	const ID floor = rb_intern("floor");
	const ID pred = rb_intern("pred");
	const ID MAX_10_EXP = rb_intern("MAX_10_EXP");
	VALUE max_10_exp = rb_const_get_at(rb_cFloat, MAX_10_EXP);
	if (!rb_num_finite_p(a) && !rb_num_positive_p(a))
		rb_raise(rb_eRangeError, "parameter a must be positive finite");
	switch (TYPE(x)) {
	case T_FIXNUM:
	case T_BIGNUM:
		*exp = x; *fra = BIG_ZERO;
		break;
	case T_FLOAT:
		if (isinf(NUM2DBL(x)) || isnan(NUM2DBL(x)))
		{
			*exp = rb_BigDecimal_flo(x); *fra = BIG_ZERO;
		}
		else
		{
			*exp = rb_funcall(x, floor, 0);
			*fra = rb_BigDecimal_flo(rb_funcall1(x, '%', INT2FIX(1)));
		}
		break;
	case T_RATIONAL:
		*exp = rb_funcall(x, floor, 0);
		*fra = rb_BigDecimal(rb_funcall1(x, '%', INT2FIX(1)), prec);
		break;
	case T_COMPLEX:
		rb_raise(rb_eTypeError, "no solution for Complex");
		break;
	default:
		if (rb_class_superclass(CLASS_OF(x)) == rb_cNumeric)
		{
			if (CLASS_OF(x) == rb_cBigDecimal)
			{
				if (!rb_num_finite_p(x))
				{
					*exp = x; *fra = BIG_ZERO;
				}
				else
				{
					*exp = rb_Integer(rb_funcall(x, fix, 0));
					if (rb_num_negative_p(x) &&
					    rb_num_notequal_p(*exp, x))
						*exp = rb_funcall(*exp, pred, 0);
					if (rb_num_notequal_p(*exp, x))
					{
						*fra = rb_funcall(x, frac, 0);
						if (rb_num_negative_p(*fra))
							*fra = rb_funcall1(BIG_ONE, '+', *fra);
					}
					else
						*fra = BIG_ZERO;
				}
			}
			else
				rb_raise(rb_eTypeError, "unknown numeric type");
		}
		rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
		break;
	}
	if (!rb_num_finite_p(x))
	{
		switch (rb_num_infinite_p(x)) {
		case 1:
			*exp = x;
			break;
		case -1:
			*exp = BIG_ZERO;
			break;
		default:
			*exp = BIG_NAN;
			break;
		}
		*fra = BIG_ZERO;
		return;
	}
	*exp = rb_bigmath_intpower(a, *exp,
		NUM2INT(rb_num_cmpeql(prec, max_10_exp)) == 1 ? prec : max_10_exp);
	*exp = rb_num_round(*exp,
		NUM2INT(rb_num_cmpeql(prec, max_10_exp)) == 1 ? prec : max_10_exp);
}


/**
 * Exponentially-decompose into the form of
 * [a ** x.floor, x % 1].
 * <br>
 * Where `escalb' mean "Exponential SCALe Binary".
 * <br>
 * It behaves as if the decomposition target of +frexp()+ in C/C++ is an exponential function.
 * 
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
edf_escalb(VALUE unused_obj, VALUE a, VALUE x, VALUE prec)
{
	VALUE exp = Qundef, fra = Qundef;
	rb_bigmath_escalb(a, x, prec, &exp, &fra);
	if (exp == Qundef || fra == Qundef)
		rb_raise(rb_eRuntimeError, "no solution");
	exp = rb_num_round(exp, prec);
	fra = rb_num_round(fra, prec);
	return rb_assoc_new(exp, fra);
}


static inline bool
check_eps(VALUE x, VALUE prec)
{
	const ID exponent = rb_intern("exponent");
	return (rb_num_negative_p(
		rb_funcall1(
			rb_funcall(x, exponent, 0),
			'+', prec
	)));
}


static VALUE
rb_bigmath_expxt(VALUE x, VALUE t, VALUE prec)
{
	const ID add = rb_intern("add");
	const ID mult = rb_intern("mult");
	const ID div = rb_intern("div");
	const ID double_fig = rb_intern("double_fig");
	VALUE m = rb_funcall1(prec, '+', 
		rb_funcall(rb_cBigDecimal, double_fig, 0));
	VALUE a = BIG_ONE;
	VALUE xt = rb_funcall1(x, '*', t);
	VALUE e = BIG_ZERO;
	long n = 0;
	if (rb_num_zero_p(xt))
		return e;
	while (!check_eps(a, m))
	{
		e = rb_funcall(e, add, 2, a, m);
		a = rb_funcall(a, div, 2, LONG2NUM(++n), m);
		a = rb_funcall(a, mult, 2, xt, m);
	}
	return rb_num_round(e, prec);
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
edf_expxt(VALUE unused_obj, VALUE x, VALUE t, VALUE prec)
{
	rb_check_precise(prec);
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	if (rb_num_notequal_p(x, x) ||
	    rb_num_negative_p(x) || 
	    NUM2INT(rb_num_cmpeql(x, INT2FIX(1))) != -1)
		rb_raise(rb_eRangeError, "Argument x is out of range: (0 <= x < 1)");
	t = rb_num_canonicalize(t, prec, ARG_REAL, ARG_RAWVALUE);
	if (rb_num_notequal_p(t, t) ||
	    rb_num_negative_p(t) ||
	    NUM2INT(rb_num_cmpeql(t, INT2FIX(1))) == 1)
		rb_raise(rb_eRangeError, "Argument t is out of range: (0 <= t <= 1)");
	return rb_bigmath_expxt(x, t, prec);
}


VALUE
rb_bigmath_exp(VALUE x, VALUE prec)
{
	const ID mult = rb_intern("mult");
	VALUE exp = Qundef, fra = Qundef;
	if (rb_num_notequal_p(x, x))
		return BIG_NAN;
	rb_bigmath_escalb(rb_bigmath_const_e(prec), x, prec, &exp, &fra);
	if (exp == Qundef || fra == Qundef)
		rb_raise(rb_eRuntimeError, "no solution");
	if (rb_num_infinite_p(exp) ||
	    rb_num_zero_p(exp) ||
	    rb_num_zero_p(fra))
		return rb_num_round(exp, prec);
	fra = rb_bigmath_expxt(fra, INT2FIX(1), prec);
	if (CLASS_OF(exp) != rb_cBigDecimal)
		exp = rb_num_canonicalize(exp, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_funcall(exp, mult, 2, fra, prec);
}

/**
 * Computes exponential function of +x+.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::EDF.exp(1, 20)
 *  #=> 0.27182818284590452354e1
 * @since 0.1.0
 */
static VALUE
edf_math_exp(VALUE unused_obj, VALUE x, VALUE prec)
{
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_bigmath_exp(x, prec);
}


static VALUE
rb_bigmath_exp2(VALUE x, VALUE prec)
{
	const ID mult = rb_intern("mult");
	VALUE exp = Qundef, fra = Qundef;
	if (rb_num_notequal_p(x, x))
		return BIG_NAN;
	rb_bigmath_escalb(INT2FIX(2), x, prec, &exp, &fra);
	if (exp == Qundef || fra == Qundef)
		rb_raise(rb_eRuntimeError, "no solution");
	if (rb_num_infinite_p(exp) ||
	    rb_num_zero_p(exp) ||
	    rb_num_zero_p(fra))
		return rb_num_round(exp, prec);
	fra = rb_bigmath_expxt(fra, rb_bigmath_const_log2(prec), prec);
	if (CLASS_OF(exp) != rb_cBigDecimal)
		exp = rb_num_canonicalize(exp, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_funcall(exp, mult, 2, fra, prec);
}

/**
 * Computes binary exponent of +x+.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::EDF.exp2(1/2r, 20)
 *  #=> 0.14142135623730950488e1
 * @since 0.1.0
 */
static VALUE
edf_math_exp2(VALUE unused_obj, VALUE x, VALUE prec)
{
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_bigmath_exp2(x, prec);
}



/**
 * Entity of rcm2(). It is equivalent to the following Ruby code:
 *
 * ```ruby
 * def rcm2(x)
 *   reso = 0
 *   fra = x
 *   if x.finite? and x.nonzero?
 *     fra = Rational(fra.abs)
 *     has_sign = x < 0
 *     case
 *     when fra >= 1
 *       while 2 <= fra
 *         reso += 1
 *         fra /= 2
 *       end
 *     else
 *       while 1 > fra
 *         reso -= 1
 *         fra *= 2
 *       end
 *     end
 *     fra = -fra if has_sign
 *   end
 *   [fra, reso]
 * end
 */
static VALUE
rcm2_inline(VALUE x, VALUE *reso)
{
	VALUE fra = x; *reso = INT2FIX(0);
	if (rb_num_nonzero_p(fra) && rb_num_finite_p(fra))
	{
		long resov = 0;
		bool has_sign = RTEST(rb_num_coerce_cmp(x, INT2FIX(0), '<'));
		VALUE rat_two = rb_rational_new1(INT2FIX(2));
		fra = rb_Rational1(fra);
		if (rb_num_negative_p(fra))
			fra = rb_num_uminus(fra);
		if (RTEST(rb_num_coerce_cmp(fra, INT2FIX(1), rb_intern(">="))))
		{
			while (RTEST(rb_num_coerce_cmp(INT2FIX(2), fra, rb_intern("<="))))
			{
				fra = rb_funcall1(fra, '/', rat_two);
				resov++;
			}
		}
		else
		{
			while (RTEST(rb_num_coerce_cmp(INT2FIX(1), fra, '>')))
			{
				fra = rb_funcall1(fra, '*', rat_two);
				resov--;
			}
		}
		if (has_sign)
			fra = rb_num_uminus(fra);
		*reso = LONG2FIX(resov);
	}
	return fra;
}

/**
 * Based on the radix complementation method, exponentially-decompose +x+ on radix 2.
 * <br>
 * It behaves the same as frexp() in C except that the value range is 1 leq y lt 2 with its exponent.
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
edf_rcm2(VALUE unused_obj, VALUE x)
{
	VALUE exp, fra;
	fra = rcm2_inline(x, &exp);
	return rb_assoc_new(fra, exp);
}

/**
 * Entity of rcm10(). It is equivalent to the following Ruby code:
 * 
 * ```ruby
 * def rcm10(x)
 *   reso = 0
 *   fra = x
 *   if x.finite? and x.nonzero?
 *     fra = Rational(fra.abs)
 *     has_sign = x < 0
 *     case
 *     when fra >= 10
 *       while fra >= 10
 *         reso += 1
 *         fra /= 10
 *       end
 *     when fra < 1
 *       while fra < 1
 *         reso -= 1
 *         fra *= 10
 *       end
 *     end
 *     fra = -fra if has_sign
 *   end
 *   [fra, reso]
 * end
 * ```
 */
static VALUE
rcm10_inline(VALUE x, VALUE *reso)
{
	VALUE fra = x; *reso = INT2FIX(0);
	if (rb_num_nonzero_p(fra) && rb_num_finite_p(fra))
	{
		long resov = 0;
		bool has_sign = RTEST(rb_num_coerce_cmp(x, INT2FIX(0), '<'));
		VALUE rat_ten = rb_rational_new1(INT2FIX(10));
		fra = rb_Rational1(fra);
		if (rb_num_negative_p(fra))
			fra = rb_num_uminus(fra);
		if (RTEST(rb_num_coerce_cmp(fra, INT2FIX(10), rb_intern(">="))))
		{
			while (RTEST(rb_num_coerce_cmp(fra, INT2FIX(10), rb_intern(">="))))
			{
				fra = rb_funcall1(fra, '/', rat_ten);
				resov++;
			}
		}
		else if (RTEST(rb_num_coerce_cmp(fra, INT2FIX(1), '<')))
		{
			while (RTEST(rb_num_coerce_cmp(fra, INT2FIX(1), '<')))
			{
				fra = rb_funcall1(fra, '*', rat_ten);
				resov--;
			}
		}
		if (has_sign)
			fra = rb_num_uminus(fra);
		*reso = LONG2FIX(resov);
	}
	return fra;
}

/**
 * Based on the radix complementation method, exponentially-decompose +x+ on radix 10.
 * <br>
 * It behaves the same as frexp() in C except that the radix is 10 and the value range is 1 leq y lt 10.
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
edf_rcm10(VALUE unused_obj, VALUE x)
{
	VALUE exp, fra;
	fra = rcm10_inline(x, &exp);
	return rb_assoc_new(fra, exp);
}

/**
 * Entity of logxt(). It is equivalent to the following Ruby code:
 * 
 * ```ruby
 *  def logxt(x, t, prec)
 *    eps = 10 ** (-prec-1)
 *    a = Rational(x); b = 1r; s = 0r;
 *    loop do
 *      a = (a * a).round(prec);  b = 0.5r * b;
 *      if a >= t
 *        s = s + b; a = a / t; 
 *      end
 *      break unless (b >= eps)
 *    end
 *    BigDecimal(s, prec)
 *  end
 *
 * ```
 */
static VALUE
logxt_inline(VALUE x, VALUE t, VALUE prec)
{
	const ID mult = rb_intern("mult");
	VALUE a, b, s, one_half, n, m;
	n = rb_numdiff_make_n(prec);
	a = rb_num_canonicalize(x, n, ARG_REAL, ARG_RAWVALUE);
	b = BIG_ONE;
	s = BIG_ZERO;
	one_half = rb_BigDecimal1(rb_str_new_cstr("0.5"));
	if (rb_num_zero_p(x))
		return BIG_ZERO;
	else if (rb_num_equal_p(x, INT2FIX(1)))
		return BIG_ZERO;
	while (rb_numdiff_condition_p(s, b, n, &m))
	{
		rb_numdiff_keep_fig(&m);
		a = rb_funcall(a, mult, 2, a, m);
		b = rb_funcall(one_half, mult, 2, b, m);
		if (RTEST(rb_num_coerce_cmp(a, t, rb_intern(">="))))
		{
			s = rb_funcall1(s, '+', b);
			a = rb_funcall1(a, '/', t);
		}
	}
	RB_GC_GUARD(b);
	RB_GC_GUARD(s);
	RB_GC_GUARD(one_half);
	return s;
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
edf_logxt(VALUE unused_obj, VALUE x, VALUE t, VALUE prec)
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
	return logxt_inline(x, t, prec);
}

#if USE_MERCATOR
static VALUE
log_mercator_ser(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	const ID mult = rb_intern("mult");
	VALUE n = rb_numdiff_make_n(prec);
	VALUE one = BIG_ONE;
	VALUE w = rb_num_canonicalize(x, n, ARG_REAL, ARG_RAWVALUE);
	VALUE t = one;
	VALUE d = BIG_ONE;
	VALUE y = BIG_ZERO;
	int sign = 1;
	VALUE m = Qundef;
	while (rb_numdiff_condition_p(y, d, n, &m))
	{
		rb_numdiff_keep_fig(&m);
		d = rb_funcall(w, div, 2, t, m);
		t = rb_funcall1(t, '+', one);
		w = rb_funcall(w, mult, 2, x, n);
		if (sign == 1)
			y = rb_funcall1(y, '+', d);
		else
			y = rb_funcall1(y, '-', d);
		sign *= -1;
	}
	RB_GC_GUARD(one);
	RB_GC_GUARD(w);
	RB_GC_GUARD(t);
	RB_GC_GUARD(d);
	RB_GC_GUARD(x);
	RB_GC_GUARD(y);
	return rb_num_round(y, prec);
}

static VALUE
log_mercator_ser_x(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE y;
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	y = rb_funcall1(x, '-', INT2FIX(1));
	y = rb_funcall(y, div, 2, x, prec);
	y = rb_num_uminus(y);
	return y;
}
#endif

VALUE
rb_bigmath_log(VALUE x, VALUE prec)
{
#if 0
	const ID log = rb_intern("log");
	if (rb_num_zero_p(x))
		return BIG_MINUS_INF;
	return rb_funcall(rb_mBigMath, log, 2, x, prec);
#else
	VALUE y = Qundef;

	rb_check_precise(prec);
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (!rb_num_finite_p(x))
	{
		switch (rb_num_infinite_p(x)) {
		case 1:
			y = BIG_INF;
			break;
		case -1: case 0:
		default:
			y = BIG_NAN;
			break;
		}
	}
	else if (rb_num_zero_p(x))
	{
		y = BIG_MINUS_INF;
	}
        else
        {
		if (TYPE(x) == T_COMPLEX)
			rb_raise(rb_eTypeError, "no solution for complex");
		if (rb_num_positive_p(x))
		{
			VALUE fra = Qundef, exp = Qundef;
			fra = rcm2_inline(x, &exp);
#if USE_MERCATOR
			fra = log_mercator_ser(log_mercator_ser_x(fra, prec), prec);
			fra = rb_num_uminus(fra);
			exp = rb_funcall1(exp, '*', rb_bigmath_const_log2(prec));
			y = rb_funcall1(exp, '+', fra);
#else
			fra = logxt_inline(fra, INT2FIX(2), prec);
			exp = rb_funcall1(exp, '+', fra);
			y = rb_funcall1(exp, '*', rb_bigmath_const_log2(prec));
#endif
			y = rb_num_round(y, prec);
		}
		else
			y = BIG_NAN;
	}
	return y;
#endif
}

/**
 * Computes natural logarithm of +x+.
 * <br>
 * In terms of solving real number solutions, the implementation is the same as log() in C.
 * 
 * @example
 *  BigMathR::EDF.log(2, 20) #=> 0.69314718055994530942e0
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 */
static VALUE
edf_math_log(VALUE unused_obj, VALUE x, VALUE prec)
{
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_bigmath_log(x, prec);
}

static VALUE
rb_bigmath_log2(VALUE x, VALUE prec)
{
#if USE_MERCATOR
	const ID div = rb_intern("div");
#endif

	VALUE y = Qundef;

	rb_check_precise(prec);
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (!rb_num_finite_p(x))
	{
		switch (rb_num_infinite_p(x)) {
		case 1:
			y = BIG_INF;
			break;
		case -1: case 0:
		default:
			y = BIG_NAN;
			break;
		}
	}
	else if (rb_num_zero_p(x))
	{
		y = BIG_MINUS_INF;
	}
        else
        {
		if (TYPE(x) == T_COMPLEX)
			rb_raise(rb_eTypeError, "no solution for complex");
		if (rb_num_positive_p(x))
		{
			VALUE fra = Qundef, exp = Qundef;
			fra = rcm2_inline(x, &exp);
#if USE_MERCATOR
			fra = log_mercator_ser(log_mercator_ser_x(fra, prec), prec);
			fra = rb_num_uminus(fra);
			fra = rb_funcall(fra, div, 2, rb_bigmath_const_log2(prec), prec);
#else
			fra = logxt_inline(fra, INT2FIX(2), prec);
#endif
			y = rb_funcall1(exp, '+', fra);
			y = rb_num_round(y, prec);
		}
		else
			y = BIG_NAN;
	}
	return y;
}


/**
 * Computes binary logarithm of +x+.
 * <br>
 * In terms of solving real number solutions, the implementation is the same as log2() in C.
 * 
 * @example
 *  BigMathR::EDF.log2(2, 20) #=> 0.1e1
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 */
static VALUE
edf_math_log2(VALUE unused_obj, VALUE x, VALUE prec)
{
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_bigmath_log2(x, prec);
}

static VALUE
rb_bigmath_log10(VALUE x, VALUE prec)
{
#if USE_MERCATOR
	const ID div = rb_intern("div");
#endif
	VALUE y = Qundef;

	rb_check_precise(prec);
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (!rb_num_finite_p(x))
	{
		switch (rb_num_infinite_p(x)) {
		case 1:
			y = BIG_INF;
			break;
		case -1: case 0:
		default:
			y = BIG_NAN;
			break;
		}
	}
	else if (rb_num_zero_p(x))
	{
		y = BIG_MINUS_INF;
	}
        else
        {
		if (TYPE(x) == T_COMPLEX)
			rb_raise(rb_eTypeError, "no solution for complex");
		if (rb_num_positive_p(x))
		{
			VALUE fra = Qundef, exp = Qundef;
			fra = rcm10_inline(x, &exp);
#if USE_MERCATOR
			fra = log_mercator_ser(log_mercator_ser_x(fra, prec), prec);
			fra = rb_num_uminus(fra);
			fra = rb_funcall(fra, div, 2, rb_bigmath_const_log10(prec), prec);
#else
			fra = logxt_inline(fra, INT2FIX(10), prec);
#endif
			y = rb_funcall1(exp, '+', fra);
			y = rb_num_round(y, prec);
		}
		else
			y = BIG_NAN;
	}
	return y;
}


/**
 * Computes common logarithm of +x+.
 * <br>
 * In terms of solving real number solutions, the implementation is the same as log10() in C.
 * 
 * @example
 *  BigMathR::EDF.log10(2, 30) #=> 0.301029995663981195213738894724e0
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 */
static VALUE
edf_math_log10(VALUE unused_obj, VALUE x, VALUE prec)
{
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_bigmath_log10(x, prec);
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
 *  Natural logatithm:        +log()+  <br>
 *  Binary logatithm:         +log2()+ <br>
 *  Common logatithm:         +log10()+ <br>
 *  
 *  Reference::
 *  {https://github.com/tribusonz-2/edf Exponential Decomposition Formula}
 */
void
InitVM_EDF(void)
{
	rb_define_module_function(rb_mEDF, "integer_power", edf_integer_power, 3);
	rb_define_module_function(rb_mEDF, "escalb", edf_escalb, 3);
	rb_define_module_function(rb_mEDF, "expxt", edf_expxt, 3);

	rb_define_module_function(rb_mEDF, "rcm2", edf_rcm2, 1);
	rb_define_module_function(rb_mEDF, "rcm10", edf_rcm10, 1);

	rb_define_module_function(rb_mEDF, "logxt", edf_logxt, 3);

	rb_define_module_function(rb_mEDF, "exp", edf_math_exp, 2);
	rb_define_module_function(rb_mEDF, "exp2", edf_math_exp2, 2);

	rb_define_module_function(rb_mEDF, "log", edf_math_log, 2);
	rb_define_module_function(rb_mEDF, "log2", edf_math_log2, 2);
	rb_define_module_function(rb_mEDF, "log10", edf_math_log10, 2);

}
