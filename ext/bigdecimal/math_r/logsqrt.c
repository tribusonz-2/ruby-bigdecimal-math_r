/*******************************************************************************
	logsqrt.c -- Logarithm & Square Root

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"

#define rb_Complex_I rb_Complex(INT2FIX(0), INT2FIX(1))
#define rb_Complex_mI rb_Complex(INT2FIX(0), INT2FIX(-1))

static bool
domain_p(VALUE x, VALUE range)
{
	const ID cover_p = rb_intern("cover?");
	return RTEST(rb_funcall(range, cover_p, 1, x));
}



static VALUE
atan_euler_ser(VALUE x, VALUE prec)
{
	const ID add = rb_intern("add");
	const ID mult = rb_intern("mult");
	const ID div = rb_intern("div");
	const ID exponent = rb_intern("exponent");
	const ID double_fig = rb_intern("double_fig");
	VALUE m, y, w, t, s;
	long n = 1;
	if (rb_num_zero_p(x))
		return BIG_ZERO;
	m = rb_funcall1(rb_funcall(rb_cBigDecimal, double_fig, 0), '+', prec);
	y = rb_funcall(
		rb_funcall(x, mult, 2, x, m), div, 2,
		rb_funcall(BIG_ONE, add, 2, rb_funcall(x, mult, 2, x, m),
		m), m);
	w = BIG_ONE;
	t = BIG_ONE;
	s = BIG_ZERO;
	for ( ; ; )
	{
		VALUE a = rb_funcall(t, mult, 2, w, m);

		if (rb_num_negative_p(rb_funcall1(m, '+', rb_funcall(a, exponent, 0))))
			break;
		s = rb_funcall(s, add, 2, a, m);
		t = rb_funcall(t, mult, 2, LONG2NUM(++n), m);
		t = rb_funcall(t, div, 2, LONG2NUM(++n), m);
		w = rb_funcall(w, mult, 2, y, m);
	};
	return rb_funcall(rb_funcall(y, div, 2, x, prec), mult, 2, s, prec);
}


VALUE
rb_bigmath_atan_cb(VALUE x, VALUE prec, VALUE (*atan_func)(VALUE x, VALUE prec))
{
#if 0
	const ID atan = rb_intern("atan");
	return rb_funcall(rb_mBigMath, atan, 2, x, prec);
#else
	const ID add = rb_intern("add");
	const ID sub = rb_intern("sub");
	const ID div = rb_intern("div");
	const ID round = rb_intern("round");
	const ID sqrt = rb_intern("sqrt");
	bool neg, dbl, inv;
	VALUE pi;
	if (!atan_func)
		atan_func = atan_euler_ser;
	rb_check_precise(prec);
	if (rb_num_notequal_p(x, x))
		return BIG_NAN;
	if (rb_num_zero_p(x))
		return rb_bigmath_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	pi = rb_bigmath_pi(prec);
	neg = rb_num_negative_p(x);
	if (neg)
		x = rb_num_uminus(x);
	if (rb_num_infinite_p(x) != 0)
		return rb_funcall(pi, div, 2,
			neg ? INT2NUM(-2) : INT2NUM(2), prec);
	if (rb_num_equal_p(rb_funcall(x, round, 1, prec), INT2FIX(1)))
		return rb_funcall(pi, div, 2,
			neg ? INT2NUM(-4) : INT2NUM(4), prec);
	inv = RTEST(rb_num_coerce_cmp(x, INT2FIX(1), '>'));
	if (inv)
		x = rb_funcall(BIG_ONE, div, 2, x, prec);
	x = rb_bigmath_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	dbl = RTEST(rb_num_coerce_cmp(x, DBL2NUM(0.5), '>'));
	if (dbl)
		// x = (-1 + sqrt(1 + x**2, prec))/x
		x = rb_funcall1(
			rb_funcall1(INT2FIX(-1), '+', 
			rb_funcall(rb_funcall1(INT2FIX(1), '+', 
			rb_funcall1(x, '*', x)), sqrt, 1, prec)), '/', x);
	x = atan_func(x, prec);
	if (dbl)
		x = rb_funcall(x, add, 2, x, prec);
	if (inv)
		x = rb_funcall(
			rb_funcall(pi, div, 2, INT2FIX(2), prec),
		sub, 2, x, prec);
	if (neg)
		x = rb_num_uminus(x);
	return x;
#endif
}

VALUE
rb_bigmath_atan(VALUE x, VALUE prec)
{
	return rb_bigmath_atan_cb(x, prec, atan_euler_ser);
}


/**
 * Computes the inverse tangent of +x+.
 * 
 * @param x [Numeric] X-axis
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  -BigMathR::LogSqrt.atan(-1, 20).mult(4, 20)
 *  #=> 0.31415926535897932385e1
 * @since 0.1.0
 */
static VALUE
logsqrt_math_atan(VALUE unused_obj, VALUE x, VALUE prec)
{
	return rb_bigmath_atan(x, prec);
}

static VALUE
rb_bigmath_acot(VALUE x, VALUE prec)
{
	if (rb_num_zero_p(x))
	{
		const ID div = rb_intern("div");
		return rb_funcall(rb_bigmath_pi(prec), div, 2, INT2FIX(2), prec);
	}
	x = rb_bigmath_canonicalize(x, prec, ARG_REAL, ARG_RECIPROCAL);
	return rb_bigmath_atan(x, prec);
}

/**
 * Computes the inverse cotangent of +x+.
 * 
 * @param x [Numeric] X-axis
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::LogSqrt.acot(1, 20) * 4
 *  #=> 0.314159265358979323852e1
 * @since 0.1.0
 */
static VALUE
logsqrt_math_acot(VALUE unused_obj, VALUE x, VALUE prec)
{
	return rb_bigmath_acot(x, prec);
}


static VALUE
asinacos_domain(ID func, VALUE x, VALUE prec, bool inversion)
{
	const ID sin = rb_intern("sin");
	const ID cos = rb_intern("cos");
	const ID div = rb_intern("div");
	const ID sub = rb_intern("sub");
	VALUE t;
	if (inversion)
		x = rb_bigmath_canonicalize(x, prec, ARG_REAL, ARG_RECIPROCAL);
	else
		x = rb_bigmath_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	t = rb_funcall1(x, '*', x);
	t = rb_funcall1(INT2FIX(1), '-', t);
	t = rb_bigmath_sqrt(t, prec);
	t = rb_funcall1(x, '/', t);
	t = rb_bigmath_atan(t, prec);
	if (func == sin)
	{
		return t;
	}
	else if (func == cos)
	{
		VALUE pi_2 = rb_funcall(
			rb_bigmath_pi(prec), div, 2, INT2FIX(2), prec);
		t = rb_funcall(pi_2, sub, 2, t, prec);
		return t;
	}
	return BIG_NAN;
}

static VALUE
rb_bigmath_asin(VALUE x, VALUE prec)
{
	const ID sin = rb_intern("sin");
	VALUE domain = rb_range_new(INT2FIX(-1), INT2FIX(1), 0);
	if (domain_p(x, domain))
		return asinacos_domain(sin, x, prec, ARG_RAWVALUE);
	else
		return BIG_NAN;
}

/**
 * Computes the inverse sine of +x+.
 * 
 * @param x [Numeric] X-axis
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::LogSqrt.asin(1, 20)
 *  #=> 0.15707963267948966193e1
 * @since 0.1.0
 */
static VALUE
logsqrt_math_asin(VALUE unused_obj, VALUE x, VALUE prec)
{
	return rb_bigmath_asin(x, prec);
}

static VALUE
rb_bigmath_acsc(VALUE x, VALUE prec)
{
	const ID sin = rb_intern("sin");
	const ID div = rb_intern("div");
	VALUE domain = rb_range_new(INT2FIX(-1), INT2FIX(1), 0);
	if (rb_num_equal_p(x, INT2FIX(-1)))
		return rb_funcall(rb_bigmath_pi(prec), div, 2, INT2FIX(-2), prec);
	else if (rb_num_equal_p(x, INT2FIX(1)))
		return rb_funcall(rb_bigmath_pi(prec), div, 2, INT2FIX(2), prec);
	else if (domain_p(x, domain))
		return BIG_NAN;
	else
		return asinacos_domain(sin, x, prec, ARG_RECIPROCAL);
}

/**
 * Computes the inverse cosecant of +x+.
 * 
 * @param x [Numeric] X-axis
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::LogSqrt.acsc(2, 20)
 *  #=> 0.52359877559829887308e0
 * @since 0.1.0
 */
static VALUE
logsqrt_math_acsc(VALUE unused_obj, VALUE x, VALUE prec)
{
	return rb_bigmath_acsc(x, prec);
}

static VALUE
rb_bigmath_acos(VALUE x, VALUE prec)
{
	const ID cos = rb_intern("cos");
	VALUE domain = rb_range_new(INT2FIX(-1), INT2FIX(1), 0);
	if (domain_p(x, domain))
		return asinacos_domain(cos, x, prec, ARG_RAWVALUE);
	else
		return BIG_NAN;
}

/**
 * Computes the inverse cosine of +x+.
 * 
 * @param x [Numeric] X-axis
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::LogSqrt.acos(-1, 20)
 *  #=> 0.31415926535897932386e1
 * @since 0.1.0
 */
static VALUE
logsqrt_math_acos(VALUE unused_obj, VALUE x, VALUE prec)
{
	return rb_bigmath_acos(x, prec);
}

static VALUE
rb_bigmath_asec(VALUE x, VALUE prec)
{
	const ID cos = rb_intern("cos");
	VALUE domain = rb_range_new(INT2FIX(-1), INT2FIX(1), 0);
	if (rb_num_equal_p(x, INT2FIX(-1)))
		return rb_bigmath_pi(prec);
	else if (rb_num_equal_p(x, INT2FIX(1)))
		return BIG_ZERO;
	else if (domain_p(x, domain))
		return BIG_NAN;
	else
		return asinacos_domain(cos, x, prec, ARG_RECIPROCAL);
}

/**
 * Computes the inverse secant of +x+.
 * 
 * @param x [Numeric] X-axis
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::LogSqrt.asec(2, 20)
 *  #=> 0.10471975511965977462e1
 * @since 0.1.0
 */
static VALUE
logsqrt_math_asec(VALUE unused_obj, VALUE x, VALUE prec)
{
	return rb_bigmath_asec(x, prec);
}


static VALUE
asinh_domain(VALUE x, VALUE prec, bool inversion)
{
	if (inversion)
		x = rb_bigmath_canonicalize(x, prec, ARG_REAL, ARG_RECIPROCAL);
	else
		x = rb_bigmath_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	if (rb_num_finite_p(x))
	{
		const ID add = rb_intern("add");
		VALUE t;
		bool has_sign;
		t = rb_funcall1(x, '*', x);
		t = rb_funcall1(INT2FIX(1), '+', t);
		t = rb_bigmath_sqrt(t, prec);
		if (rb_num_equal_p(
			(has_sign = rb_num_negative_p(x)) ? rb_num_uminus(x) : x, t))
		{
			t = rb_bigmath_log(t, prec);
			t = rb_funcall(rb_bigmath_const_log2(prec), add, 2, t, prec);
			x = has_sign ? rb_num_uminus(t) : t;
		}
		else
		{
			x = rb_funcall(t, add, 2, x, prec);
			x = rb_bigmath_log(x, prec);
		}
	}
	return x;
}

static VALUE
rb_bigmath_asinh(VALUE x, VALUE prec)
{
	return asinh_domain(x, prec, ARG_RAWVALUE);
}

/**
 * Computes inverse hyperbolic sine of +x+.
 * 
 * @example
 *  BigMathR::LogSqrt.asinh(1, 20)
 *  #=> 0.88137358701954302523e0
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_asinh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return rb_bigmath_asinh(x, prec);
}

static VALUE
rb_bigmath_acsch(VALUE x, VALUE prec)
{
	return asinh_domain(x, prec, ARG_RECIPROCAL);
}

/**
 * Computes inverse hyperbolic cosecant of +x+.
 * 
 * @example
 *  BigMathR::LogSqrt.acsch(1, 20)
 *  #=> 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_acsch(VALUE unused_obj, VALUE x, VALUE prec)
{
	return rb_bigmath_acsch(x, prec);
}

static VALUE
asech_domain(VALUE x, VALUE prec)
{
	VALUE r1, r2, r3, r4, r5, r6;
	r1 = rb_funcall1(x, '*', x);
	r2 = rb_funcall1(INT2FIX(1), '-', r1);
	r3 = rb_bigmath_sqrt(r2, prec);
	r4 = rb_funcall1(r3, '+', INT2FIX(1));
	r5 = rb_funcall1(r4, '/', x);
	r6 = rb_bigmath_log(r5, prec);
	return r6;
}



static VALUE
rb_bigmath_asech(VALUE x, VALUE prec)
{
	VALUE domain = rb_range_new(INT2FIX(0), INT2FIX(1), 0);
	if (domain_p(x, domain))
	{
		x = rb_bigmath_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
		return asech_domain(x, prec);
	}
	else
		return BIG_NAN;
}

/**
 * Computes inverse hyperbolic secant of +x+.
 * 
 * @example
 *  BigMathR::LogSqrt.asech(1/2r, 20)
 *  #=> 0.13169578969248167087e1
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_asech(VALUE unused_obj, VALUE x, VALUE prec)
{
	return rb_bigmath_asech(x, prec);
}

static VALUE
rb_bigmath_acosh(VALUE x, VALUE prec)
{
	VALUE domain = rb_range_new(INT2FIX(0), DBL2NUM(HUGE_VAL), 0);
	if (domain_p(x, domain))
	{
		x = rb_bigmath_canonicalize(x, prec, ARG_REAL, ARG_RECIPROCAL);
		return asech_domain(x, prec);
	}
	else
		return BIG_NAN;
}

/**
 * Computes inverse hyperbolic cosine of +x+.
 * 
 * @example
 *  BigMathR::LogSqrt.acosh(2, 20)
 *  #=> 0.13169578969248167087e1
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_acosh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return rb_bigmath_acosh(x, prec);
}

static VALUE
atanh_domain(VALUE x, VALUE prec)
{
	VALUE r1, r2, r3, r4, r5;
	const ID sqrt = rb_intern("sqrt");
	r1 = rb_funcall1(INT2FIX(1), '+', x);
	r2 = rb_funcall(r1, sqrt, 1, prec);
	r1 = rb_funcall1(INT2FIX(1), '-', x);
	r3 = rb_funcall(r1, sqrt, 1, prec);
	r4 = rb_funcall1(r2, '/', r3);
	r5 = rb_bigmath_log(r4, prec);
	return rb_bigmath_round_inline(r5, prec);
}

static VALUE
rb_bigmath_atanh(VALUE x, VALUE prec)
{
	VALUE domain = rb_range_new(INT2FIX(-1), INT2FIX(1), 0);
	if (domain_p(x, domain))
	{
		x = rb_bigmath_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
		return atanh_domain(x, prec);
	}
	else
		return BIG_NAN;
}

/**
 * Computes inverse hyperbolic tangent of +x+.
 * 
 * @example
 *  BigMathR::LogSqrt.atanh(1/3r, 20)
 *  #=> 0.34657359027997265471e0
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_atanh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return rb_bigmath_atanh(x, prec);
}

static VALUE
rb_bigmath_acoth(VALUE x, VALUE prec)
{
	VALUE domain = rb_range_new(INT2FIX(-1), INT2FIX(1), 0);
	if (rb_num_equal_p(x, INT2FIX(1)))
		return BIG_INF;
	else if (rb_num_equal_p(x, INT2FIX(-1)))
		return BIG_MINUS_INF;
	else if (!domain_p(x, domain))
	{
		if (rb_num_notequal_p(x, x))
			return BIG_NAN;
		x = rb_bigmath_canonicalize(x, prec, ARG_REAL, ARG_RECIPROCAL);
		return atanh_domain(x, prec);
	}
	else
		return BIG_NAN;
}

/**
 * Computes inverse hyperbolic cotangent of +x+.
 * 
 * @example
 *  BigMathR::LogSqrt.acoth(2, 20)
 *  #=> 0.54930614433405484568e0
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_acoth(VALUE unused_obj, VALUE x, VALUE prec)
{
	return rb_bigmath_acoth(x, prec);
}


VALUE
rb_bigmath_clog(VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	VALUE real = rb_bigmath_log(rb_bigmath_cabs(z, prec), prec);
	VALUE imag = rb_bigmath_carg(z, prec);
	return rb_Complex(real, imag);
}

/**
 * Computes complex natural logarithm of +z+.
 * 
 * @example
 *  BigMathR::LogSqrt.clog(1+1i, 20)
 *  #=> (0.34657359027997265471e0+0.78539816339744830963e0i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_clog(VALUE unused_obj, VALUE z, VALUE prec)
{
	return rb_bigmath_clog(z, prec);
}

/**
 * Computes complex binary logarithm of +z+.
 * 
 * @example
 *  BigMathR::LogSqrt.clog2(1+1i, 20)
 *  #=> (0.5e0+0.11330900354567984524e1i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_clog2(VALUE unused_obj, VALUE z, VALUE prec)
{
	VALUE w = rb_bigmath_clog(z, prec);
	w = rb_funcall1(w, '/', rb_bigmath_const_log2(prec));
	return rb_bigmath_round_inline(w, prec);
}

/**
 * Computes complex common logarithm of +z+.
 * 
 * @example
 *  BigMathR::LogSqrt.clog10(1+1i, 20)
 *  #=> (0.15051499783199059761e0+0.34109408846046033688e0i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_clog10(VALUE unused_obj, VALUE z, VALUE prec)
{
	VALUE w = rb_bigmath_clog(z, prec);
	w = rb_funcall1(w, '/', rb_bigmath_const_log10(prec));
	return rb_bigmath_round_inline(w, prec);
}

static VALUE
casin_domain(VALUE z, VALUE prec)
{
	VALUE c1 = rb_funcall1(rb_Complex_I, '*', z);
	VALUE c2 = rb_bigmath_csqrt(rb_funcall1(INT2FIX(1), '-', 
		rb_funcall1(z, '*', z)), prec);
	VALUE c3 = rb_bigmath_clog(rb_funcall1(c1, '+', c2), prec);
	return rb_funcall1(rb_Complex_mI, '*', c3);
}


static VALUE
rb_bigmath_casin(VALUE z, VALUE prec)
{
	int z_re_inf = rb_num_infinite_p(rb_num_real(z));
	int z_im_inf = rb_num_infinite_p(rb_num_imag(z));
	if (rb_num_nan_p(z))
		return rb_Complex(BIG_NAN, BIG_NAN);
	else if (z_re_inf || z_im_inf)
	{
		const ID div = rb_intern("div");
		if (z_re_inf != 0 && z_im_inf == 0)
		{
			VALUE real = rb_num_zero_p(rb_num_imag(z)) ?
				rb_funcall(rb_bigmath_pi(prec), div, 2, 
					INT2FIX(z_re_inf * 2), prec) :
				BIG_ZERO;
			VALUE imag = z_re_inf == 1 ? BIG_MINUS_INF : BIG_INF;
			return rb_Complex(real, imag);
		}
		else if (z_re_inf == 0 && z_im_inf != 0)
		{
			return rb_Complex(BIG_ZERO, rb_num_imag(z));
		}
		else if (z_re_inf == -1 && z_im_inf == 1)
			return rb_Complex(BIG_NAN, BIG_NAN);
		else
			return rb_Complex(BIG_ZERO, BIG_ZERO);
	}
	else
	{
		z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
		return casin_domain(z, prec);
	}
}


/**
 * Computes complex inverse sine of +z+.
 * 
 * @example
 *  BigMathR::LogSqrt.casin(1+1i, 20)
 *  #=> (0.6662394324925152551e0+0.1061275061905035652e1i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_casin(VALUE unused_obj, VALUE z, VALUE prec)
{
	return rb_bigmath_casin(z, prec);
}

#if 0
static VALUE
cacsc_domain(VALUE z, VALUE prec)
{
	VALUE c1, c2, c3, c4, c5, c6, c7;
	c1 = rb_funcall1(z, '*', z);
	c2 = rb_funcall1(INT2FIX(1), '/', c1);
	c3 = rb_funcall1(INT2FIX(1), '-', c2);
	c4 = rb_bigmath_csqrt(c3, prec);
	c5 = rb_funcall1(c4, '+', rb_funcall1(rb_Complex_I, '/', z));
	c6 = rb_bigmath_clog(c5, prec);
	c7 = rb_funcall1(rb_Complex_mI, '*', c6);
	return rb_bigmath_round_inline(c7, prec);
}
#endif

static VALUE
rb_bigmath_cacsc(VALUE z, VALUE prec)
{
	int z_re_inf = rb_num_infinite_p(rb_num_real(z));
	int z_im_inf = rb_num_infinite_p(rb_num_imag(z));
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	if (rb_num_nan_p(z))
		return rb_Complex(BIG_NAN, BIG_NAN);
	else if (z_re_inf || z_im_inf)
	{
		return rb_Complex(BIG_ZERO, BIG_ZERO);
	}
	else if (rb_num_zero_p(z))
	{
		const ID div = rb_intern("div");
		int zero_sign = NUM2INT(rb_BigDecimal_sign(rb_num_real(z)));
		VALUE real = rb_num_nonzero_p(rb_num_imag(z)) ?
			BIG_ZERO : rb_funcall(rb_bigmath_pi(prec), div, 2, 
			INT2FIX(zero_sign * 2), prec);
		VALUE imag = 1 == zero_sign ? BIG_MINUS_INF : BIG_INF;
		return rb_Complex(real, imag);
	}
	else
	{
		z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RECIPROCAL);
		return casin_domain(z, prec);
	}
}


/**
 * Computes complex inverse cosecant of +z+.
 * 
 * @example
 *  BigMathR::LogSqrt.cacsc(1+1i, 20)
 *  #=> (0.45227844715119068206e0-0.53063753095251782602e0i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_cacsc(VALUE unused_obj, VALUE z, VALUE prec)
{
	return rb_bigmath_cacsc(z, prec);
}

static VALUE
cacos_domain(VALUE z, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE c1 = rb_funcall1(rb_Complex_I, '*', z);
	VALUE c2 = rb_bigmath_csqrt(rb_funcall1(INT2FIX(1), '-', 
		rb_funcall1(z, '*', z)), prec);
	VALUE c3 = rb_bigmath_clog(rb_funcall1(c1, '+', c2), prec);
	VALUE c4 = rb_funcall1(rb_Complex_I, '*', c3);
	VALUE c5 = rb_funcall(rb_bigmath_pi(prec), div, 2, INT2FIX(2), prec);
	VALUE c6 = rb_funcall1(c5, '+', c4);
	return rb_bigmath_round_inline(c6, prec);
}


static VALUE
rb_bigmath_cacos(VALUE z, VALUE prec)
{
	int z_re_inf = rb_num_infinite_p(rb_num_real(z));
	int z_im_inf = rb_num_infinite_p(rb_num_imag(z));
	if (rb_num_nan_p(z))
		return rb_Complex(BIG_NAN, BIG_NAN);
	else if (z_re_inf || z_im_inf)
	{
		if (z_re_inf != 0 && z_im_inf == 0)
		{
			VALUE real = 
				(rb_num_zero_p(rb_num_imag(z)) &&
			         z_re_inf == 1) ?
				BIG_ZERO : rb_bigmath_pi(prec);
			VALUE imag = z_re_inf == 1 ? BIG_MINUS_INF : BIG_INF;
			return rb_Complex(real, imag);
		}
		else if (z_re_inf == 0 && z_im_inf != 0)
		{
			return rb_Complex(BIG_ZERO, rb_num_imag(z));
		}
		else if (z_re_inf == -1 && z_im_inf == 1)
			return rb_Complex(BIG_NAN, BIG_NAN);
		else
			return rb_Complex(BIG_ZERO, BIG_ZERO);
	}
	else
	{
		z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
		return cacos_domain(z, prec);
	}
}

/**
 * Computes complex inverse cosine of +z+.
 * 
 * @example
 *  BigMathR::LogSqrt.cacos(1+1i, 20)
 *  #=> (0.9045568943023813642e0-0.1061275061905035652e1i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_cacos(VALUE unused_obj, VALUE z, VALUE prec)
{
	return rb_bigmath_cacos(z, prec);
}


#if 0
static VALUE
casec_domain(VALUE z, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE c1 = rb_funcall1(z, '*', z);
	VALUE c2 = rb_funcall1(INT2FIX(1), '/', c1);
	VALUE c3 = rb_funcall1(INT2FIX(1), '-', c2);
	VALUE c4 = rb_bigmath_csqrt(c3, prec);
	VALUE c5 = rb_funcall1(c4, '+', rb_funcall1(rb_Complex_I, '/', z));
	VALUE c6 = rb_bigmath_clog(c5, prec);
	VALUE c7 = rb_funcall1(rb_Complex_I, '*', c6);
	VALUE c8 = rb_funcall(rb_bigmath_pi(prec), div, 2, INT2FIX(2), prec);
	VALUE c9 = rb_funcall1(c8, '+', c7);

	return rb_bigmath_round_inline(c9, prec);
}
#endif

static VALUE
rb_bigmath_casec(VALUE z, VALUE prec)
{
	int z_re_inf = rb_num_infinite_p(rb_num_real(z));
	int z_im_inf = rb_num_infinite_p(rb_num_imag(z));
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	if (rb_num_nan_p(z))
		return rb_Complex(BIG_NAN, BIG_NAN);
	else if (z_re_inf || z_im_inf)
	{
		return rb_Complex(BIG_ZERO, BIG_ZERO);
	}
	else if (rb_num_zero_p(z))
	{
		int zero_sign = NUM2INT(rb_BigDecimal_sign(rb_num_real(z)));
		VALUE real = 
			(rb_num_nonzero_p(rb_num_imag(z)) || zero_sign == -1) ?
			BIG_ZERO : rb_bigmath_pi(prec);
		VALUE imag = 1 == zero_sign ? BIG_MINUS_INF : BIG_INF;
		return rb_Complex(real, imag);
	}
	else
	{
		z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RECIPROCAL);
		return cacos_domain(z, prec);
	}
}

/**
 * Computes complex inverse secant of +z+.
 * 
 * @example
 *  BigMathR::LogSqrt.casec(1+1i, 20)
 *  #=> (0.11185178796437059372e1+0.53063753095251782602e0i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_casec(VALUE unused_obj, VALUE z, VALUE prec)
{
	return rb_bigmath_casec(z, prec);
}


static VALUE
catan_domain(VALUE z, VALUE prec)
{
	VALUE c1, c2, c3, c4;
	c1 = rb_funcall1(rb_Complex_I, '*', z);
	c2 = rb_funcall1(INT2FIX(1), '-', c1);
	c3 = rb_bigmath_clog(c2, prec);

	c1 = rb_funcall1(rb_Complex_I, '*', z);
	c2 = rb_funcall1(INT2FIX(1), '+', c1);
	c4 = rb_bigmath_clog(c2, prec);

	c1 = rb_funcall1(c3, '-', c4);
	c2 = rb_Complex(INT2FIX(0), rb_Rational(INT2FIX(1), INT2FIX(2)));
	c3 = rb_funcall1(c2, '*', c1);
	return rb_bigmath_round_inline(c3, prec);
}

static VALUE
rb_bigmath_catan(VALUE z, VALUE prec)
{
	int z_re_inf = rb_num_infinite_p(rb_num_real(z));
	int z_im_inf = rb_num_infinite_p(rb_num_imag(z));
	if (rb_num_nan_p(z))
		return rb_Complex(BIG_NAN, BIG_NAN);
	else if (z_re_inf || z_im_inf)
	{
		const ID div = rb_intern("div");
		if (z_re_inf != 0 && z_im_inf == 0)
		{
			VALUE real = 
				rb_funcall(rb_bigmath_pi(prec), div, 2, 
				INT2FIX(z_re_inf * 2), prec);
			VALUE imag = BIG_ZERO;
			return rb_Complex(real, imag);
		}
		else if (z_re_inf == 0 && z_im_inf != 0)
		{
			VALUE real = 
				rb_funcall(rb_bigmath_pi(prec), div, 2, 
				INT2FIX(z_im_inf * 2), prec);
			VALUE imag = BIG_ZERO;
			return rb_Complex(real, imag);
		}
		else if (z_re_inf == -1 && z_im_inf == 1)
			return rb_Complex(BIG_NAN, BIG_NAN);
		else
			return rb_Complex(BIG_ZERO, BIG_ZERO);
	}
	else if (rb_num_equal_p(z, rb_Complex_I))
		return rb_Complex(BIG_ZERO, BIG_INF);
	else if (rb_num_equal_p(z, rb_Complex_mI))
		return rb_Complex(BIG_ZERO, BIG_MINUS_INF);
	else
	{
		z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
		return catan_domain(z, prec);
	}
}

/**
 * Computes complex inverse tangent of +z+.
 * 
 * @example
 *  BigMathR::LogSqrt.catan(1+1i, 20)
 *  #=> (0.10172219678978513678e1+0.40235947810852509365e0i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_catan(VALUE unused_obj, VALUE z, VALUE prec)
{
	return rb_bigmath_catan(z, prec);
}

#if 0
static VALUE
cacot_domain(VALUE z, VALUE prec)
{
	VALUE c1, c2, c3, c4;
	c1 = rb_funcall1(z, '-', rb_Complex_I);;
	c2 = rb_funcall1(c1, '/', z);
	c3 = rb_bigmath_clog(c2, prec);
	c1 = rb_funcall1(z, '+', rb_Complex_I);;
	c2 = rb_funcall1(c1, '/', z);
	c4 = rb_bigmath_clog(c2, prec);
	c2 = rb_funcall1(c3, '-', c4);
	c1 = rb_funcall1(rb_BigDecimal1(rb_str_new_cstr("0.5")), '*', rb_Complex_I);
	c3 = rb_funcall1(c1, '*', c2);
	return rb_bigmath_round_inline(c3, prec);
}
#endif

static VALUE
rb_bigmath_cacot(VALUE z, VALUE prec)
{
	int z_re_inf = rb_num_infinite_p(rb_num_real(z));
	int z_im_inf = rb_num_infinite_p(rb_num_imag(z));
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	if (rb_num_nan_p(z))
		return rb_Complex(BIG_NAN, BIG_NAN);
	else if (z_re_inf || z_im_inf)
	{
		return rb_Complex(BIG_ZERO, BIG_ZERO);
	}
	else if (rb_num_equal_p(z, rb_Complex_I))
	{
		return rb_Complex(BIG_ZERO, BIG_MINUS_INF);
	}
	else if (rb_num_equal_p(z, rb_Complex_mI))
	{
		return rb_Complex(BIG_ZERO, BIG_INF);
	}
	else if (rb_num_zero_p(z))
	{
		const ID div = rb_intern("div");
		VALUE real = 
			rb_funcall(rb_bigmath_pi(prec), div, 2, INT2FIX(2), prec);
		return rb_Complex(real, BIG_ZERO);
	}
	else
	{
		z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RECIPROCAL);
		return catan_domain(z, prec);
	}
}

/**
 * Computes complex inverse cotangent of +z+.
 * 
 * @example
 *  BigMathR::LogSqrt.cacot(1+1i, 20)
 *  #=> (0.55357435889704525152e0-0.40235947810852509365e0i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_cacot(VALUE unused_obj, VALUE z, VALUE prec)
{
	return rb_bigmath_cacot(z, prec);
}


static VALUE
rb_bigmath_casinh(VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	z = rb_ImaginaryZ(z, SIGN_PLUS);
	z = rb_bigmath_casin(z, prec);
	return rb_ImaginaryZ(z, SIGN_MINUS);
}

/**
 * Computes complex inverse hyperbolic sine of +z+.
 * 
 * @example
 *  BigMathR::LogSqrt.casinh(1+1i, 20)
 *  #=> (0.1061275061905035652e1+0.6662394324925152551e0i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_casinh(VALUE unused_obj, VALUE z, VALUE prec)
{
	return rb_bigmath_casinh(z, prec);
}

static VALUE
rb_bigmath_cacsch(VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	if (rb_num_zero_p(rb_num_imag(z)))
		return rb_Complex(rb_bigmath_acsch(z, prec), BIG_ZERO);
	z = rb_ImaginaryZ(z, SIGN_PLUS);
	z = rb_bigmath_cacsc(z, prec);
	return rb_ImaginaryZ(z, SIGN_PLUS);
}

/**
 * Computes complex inverse hyperbolic cosecant of +z+.
 * 
 * @example
 *  BigMathR::LogSqrt.cacsch(1+1i, 20)
 *  #=> (0.53063753095251782602e0-0.45227844715119068206e0i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_cacsch(VALUE unused_obj, VALUE z, VALUE prec)
{

	return rb_bigmath_cacsch(z, prec);
}

static VALUE
cacosh_domain(VALUE z, VALUE prec)
{
	VALUE c1, c2, c3;
	c2 = rb_funcall1(z, '+', INT2FIX(1));
	c2 = rb_bigmath_csqrt(c2, prec);
	c3 = rb_funcall1(z, '-', INT2FIX(1));
	c3 = rb_bigmath_csqrt(c3, prec);
	c1 = rb_funcall1(c2, '*', c3);
	c1 = rb_funcall1(z, '+', c1);
	c1 = rb_bigmath_clog(c1, prec);
	return c1;
}

static VALUE
rb_bigmath_cacosh(VALUE z, VALUE prec)
{
	int z_re_inf = rb_num_infinite_p(rb_num_real(z));
	int z_im_inf = rb_num_infinite_p(rb_num_imag(z));
	if (rb_num_nan_p(z))
		return rb_Complex(BIG_NAN, BIG_NAN);
	else if (z_re_inf || z_im_inf)
	{
		if (z_re_inf != 0 && z_im_inf == 0)
		{
			VALUE real = BIG_INF;
			VALUE imag = (z_re_inf == -1 && rb_num_zero_p(rb_num_imag(z))) ? 
				rb_bigmath_pi(prec) : BIG_ZERO;
			return rb_Complex(real, imag);
		}
		else if (z_re_inf == 0 && z_im_inf != 0)
		{
			VALUE real = BIG_INF;
			VALUE imag = BIG_ZERO;
			return rb_Complex(real, imag);
		}
		else if (z_re_inf == -1 && z_im_inf == 1)
			return rb_Complex(BIG_NAN, BIG_NAN);
		else
			return rb_Complex(BIG_ZERO, BIG_ZERO);
	}
	else
	{
		z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
		return cacosh_domain(z, prec);
	}
}

/**
 * Computes complex inverse hyperbolic cosine of +z+.
 * 
 * @example
 *  BigMathR::LogSqrt.cacosh(1+1i, 20)
 *  #=> (0.1061275061905035652e1+0.9045568943023813642e0i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_cacosh(VALUE unused_obj, VALUE z, VALUE prec)
{
	return rb_bigmath_cacosh(z, prec);
}

static VALUE
rb_bigmath_casech(VALUE z, VALUE prec)
{
	int z_re_inf = rb_num_infinite_p(rb_num_real(z));
	int z_im_inf = rb_num_infinite_p(rb_num_imag(z));
	if (rb_num_nan_p(z))
		return rb_Complex(BIG_NAN, BIG_NAN);
	else if (z_re_inf || z_im_inf)
	{
		const ID div = rb_intern("div");
		if (z_re_inf != 0 && z_im_inf == 0)
		{
			VALUE imag = rb_funcall(rb_bigmath_pi(prec), div, 
				2, INT2FIX(2), prec);
			return rb_Complex(BIG_ZERO, imag);
		}
		else if (z_re_inf == 0 && z_im_inf != 0)
		{
			VALUE imag = rb_funcall(rb_bigmath_pi(prec), div, 
				2, INT2FIX(-2 * z_im_inf), prec);
			return rb_Complex(BIG_ZERO, imag);
		}
		else if (z_re_inf == -1 && z_im_inf == 1)
			return rb_Complex(BIG_NAN, BIG_NAN);
		else
			return rb_Complex(BIG_ZERO, BIG_ZERO);
	}
	else
	{
		z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RECIPROCAL);
		return cacosh_domain(z, prec);
	}
}

/**
 * Computes complex inverse hyperbolic secant of +z+.
 * 
 * @example
 *  BigMathR::LogSqrt.casech(1+1i, 20)
 *  #=> 
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_casech(VALUE unused_obj, VALUE z, VALUE prec)
{
	return rb_bigmath_casech(z, prec);
}

static VALUE
rb_bigmath_catanh(VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	z = rb_ImaginaryZ(z, SIGN_PLUS);
	z = rb_bigmath_catan(z, prec);
	return rb_ImaginaryZ(z, SIGN_MINUS);
}

/**
 * Computes complex inverse hyperbolic tangent of +z+.
 * 
 * @example
 *  BigMathR::LogSqrt.catanh(1+1i, 20)
 *  #=> (0.40235947810852509365e0+0.10172219678978513678e1i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_catanh(VALUE unused_obj, VALUE z, VALUE prec)
{
	return rb_bigmath_catanh(z, prec);
}

static VALUE
rb_bigmath_cacoth(VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	z = rb_ImaginaryZ(z, SIGN_MINUS);
	z = rb_bigmath_cacot(z, prec);
	return rb_ImaginaryZ(z, SIGN_MINUS);
}

/**
 * Computes complex inverse hyperbolic cotangent of +z+.
 * 
 * @example
 *  BigMathR::LogSqrt.cacoth(1+1i, 20)
 *  #=> (0.40235947810852509365e0-0.55357435889704525152e0i)
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
logsqrt_math_cacoth(VALUE unused_obj, VALUE z, VALUE prec)
{
	return rb_bigmath_cacoth(z, prec);
}


/**
 *  Document-module:  BigMathR::LogSqrt
 *  
 *  A module that provides using square root and logarithmic function. 
 *  It is used internally.
 *  <br>
 *  == Synopsis
 *  The function names defined are the same as those in the C/C++ standard.
 *  <br>
 *  - Natural logarithm:                     +:clog+ <br>
 *  - Binary logarithm:                      +:clog2+ <br>
 *  - Common logarithm:                      +:clog10+ <br>
 *  - Inverse sine:                 +:asin+  +:casin+ <br>
 *  - Inverse cosine:               +:acos+  +:cacos+ <br>
 *  - Inverse tangent:              +:atan+  +:catan+ <br>
 *  - Inverse hyperbolic sine:      +:asinh+ +:casinh+ <br>
 *  - Inverse hyperbolic cosine:    +:acosh+ +:cacosh+ <br>
 *  - Inverse hyperbolic tangent:   +:atanh+ +:catanh+ <br>
 *  Follow, the name defined in C/C++ standard though, the function names are different.
 *  <br>
 *  - Inverse cosecant:             +:acsc+  +:cacsc+ <br>
 *  - Inverse secant:               +:asec+  +:casec+ <br>
 *  - Inverse cotangent:            +:acot+  +:cacot+ <br>
 *  - Inverse hyperbolic cosecant:  +:acsch+ +:cacsch+ <br>
 *  - Inverse hyperbolic secant:    +:asech+ +:casech+ <br>
 *  - Inverse hyperbolic cotangent: +:acoth+ +:cacoth+ <br>
 *  Reference::
 *  {https://mathworld.wolfram.com/NaturalLogarithm.html Wolfram Mathworld - Natural Logarithm}
 */

void
InitVM_LogSqrt(void)
{
	rb_define_module_function(rb_mLogSqrt, "clog", logsqrt_math_clog, 2);
	rb_define_module_function(rb_mLogSqrt, "clog2", logsqrt_math_clog2, 2);
	rb_define_module_function(rb_mLogSqrt, "clog10", logsqrt_math_clog10, 2);

	rb_define_module_function(rb_mLogSqrt, "asin", logsqrt_math_asin, 2);
	rb_define_module_function(rb_mLogSqrt, "acos", logsqrt_math_acos, 2);
	rb_define_module_function(rb_mLogSqrt, "atan", logsqrt_math_atan, 2);
	rb_define_module_function(rb_mLogSqrt, "acsc", logsqrt_math_acsc, 2);
	rb_define_module_function(rb_mLogSqrt, "asec", logsqrt_math_asec, 2);
	rb_define_module_function(rb_mLogSqrt, "acot", logsqrt_math_acot, 2);

	rb_define_module_function(rb_mLogSqrt, "asinh", logsqrt_math_asinh, 2);
	rb_define_module_function(rb_mLogSqrt, "acosh", logsqrt_math_acosh, 2);
	rb_define_module_function(rb_mLogSqrt, "atanh", logsqrt_math_atanh, 2);
	rb_define_module_function(rb_mLogSqrt, "acsch", logsqrt_math_acsch, 2);
	rb_define_module_function(rb_mLogSqrt, "asech", logsqrt_math_asech, 2);
	rb_define_module_function(rb_mLogSqrt, "acoth", logsqrt_math_acoth, 2);

	rb_define_module_function(rb_mLogSqrt, "casin", logsqrt_math_casin, 2);
	rb_define_module_function(rb_mLogSqrt, "cacos", logsqrt_math_cacos, 2);
	rb_define_module_function(rb_mLogSqrt, "catan", logsqrt_math_catan, 2);
	rb_define_module_function(rb_mLogSqrt, "cacsc", logsqrt_math_cacsc, 2);
	rb_define_module_function(rb_mLogSqrt, "casec", logsqrt_math_casec, 2);
	rb_define_module_function(rb_mLogSqrt, "cacot", logsqrt_math_cacot, 2);

	rb_define_module_function(rb_mLogSqrt, "casinh", logsqrt_math_casinh, 2);
	rb_define_module_function(rb_mLogSqrt, "cacosh", logsqrt_math_cacosh, 2);
	rb_define_module_function(rb_mLogSqrt, "catanh", logsqrt_math_catanh, 2);
	rb_define_module_function(rb_mLogSqrt, "cacsch", logsqrt_math_cacsch, 2);
	rb_define_module_function(rb_mLogSqrt, "casech", logsqrt_math_casech, 2);
	rb_define_module_function(rb_mLogSqrt, "cacoth", logsqrt_math_cacoth, 2);

}
