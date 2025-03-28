/*******************************************************************************
	power_root.c -- Power Root

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "internal/solver/bigmath_r.h"

VALUE
rb_bigmath_sqrt(VALUE x, VALUE prec)
{
	const ID sqrt = rb_intern("sqrt");
	x = rb_bigmath_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	if (rb_num_negative_p(x) || rb_num_notequal_p(x, x))
		return BIG_NAN;
	return rb_funcall(x, sqrt, 1, prec);
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
powerroot_math_sqrt(VALUE unused_obj, VALUE x, VALUE prec)
{
	VALUE y;
	y = rb_bigmath_sqrt(x, prec);
	return rb_bigmath_round_inline(y, prec);
}

static VALUE
csqrt_term(VALUE abs, VALUE a, VALUE prec, ID ops)
{
	const ID div = rb_intern("div");
	const ID round = rb_intern("round");
	VALUE t;
	t = rb_funcall(abs, ops, 2, a, prec);
	t = rb_funcall(t, div, 2, INT2FIX(2), prec);
	if (rb_num_negative_p(t))
		return BIG_ZERO;
	t = rb_bigmath_sqrt(t, prec);
	t = rb_funcall(t, round, 1, prec);
	return t;
}

VALUE
rb_bigmath_csqrt(VALUE z, VALUE prec)
{
	VALUE w = Qundef;
	rb_check_precise(prec);
	if (!rb_num_finite_p(z))
	{
		int re_sgn, im_sgn;
		if ((re_sgn = rb_num_infinite_p(rb_num_real(z)) != 0) &&
		    (rb_num_infinite_p(rb_num_imag(z))) != 0)
		{
			switch (re_sgn) {
			case 1:
				w = rb_Complex1(BIG_INF);
				break;
			case -1:
				w = rb_Complex(BIG_ZERO, BIG_INF);
				break;
			}
		}
		else if ((im_sgn = rb_num_infinite_p(rb_num_imag(z))) != 0)
		{
			w = rb_Complex(
				BIG_INF,
				rb_num_coerce_bin(im_sgn, BIG_INF, '*')
			);
		}
		else
		{
			w = rb_Complex(BIG_NAN, BIG_NAN);
		}
	}
	else // if (rb_num_finite_p(z))
	{
		const ID add = rb_intern("add"), sub = rb_intern("sub");
		VALUE abs = rb_bigmath_cabs(z, prec),
		      re = csqrt_term(abs, rb_num_real(z), prec, add),
		      im = csqrt_term(abs, rb_num_real(z), prec, sub),
		      sgn = rb_num_cmpeql(rb_num_imag(z), INT2NUM(0));
		if (rb_num_nonzero_p(sgn))
			w = rb_Complex(re, rb_num_coerce_bin(sgn, im, '*'));
		else
			w = rb_Complex(re, im);
	}
	if (w == Qundef)
		rb_raise(rb_eRuntimeError, "no solution");
	return w;
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
powerroot_math_csqrt(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
        return rb_bigmath_csqrt(z, prec);
}


/**
 * Reference: Haruhiko Okumura - C-gengo ni yoru hyoujun algorithm jiten
 * ```Ruby
 * def cuberoot(x, prec)
 *   s, prev = BigDecimal(0)
 *   positive = 1
 *   return BigDecimal(x) if !x.finite?
 *   return BigDecimal(0) if x.zero?
 *   if x > 0
 *     positive = true
 *   else
 *     positive = false; x = -x
 *   end
 *   if x > 1
 *     s = x
 *   else
 *     s = BigDecimal(1)
 *   end
 *   loop do
 *     prev = s
 *     s = (x / (s * s) + 2 * s).div(3, prec)
 *     break if (s >= prev)
 *   end
 *   positive ? prev : -prev
 * end
 * ```
 */
static VALUE
rb_bigmath_cuberoot(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE s = Qundef, t = Qundef, prev = Qundef;
	bool positive;
	x = rb_bigmath_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	rb_check_precise(prec);
	if (!rb_num_finite_p(x) || rb_num_zero_p(x))
		return x;
	positive = rb_num_positive_p(x) ? true : false;
	if (!positive)
		x = rb_num_uminus(x);
	if (RTEST(rb_num_coerce_cmp(x, INT2FIX(1), '>')))
		s = x;
	else
		s = BIG_ONE;
	do {
		prev = s;
		t = rb_funcall1(s, '*', s);
		t = rb_funcall1(x, '/', t);
		t = rb_funcall1(t, '+', rb_funcall1(INT2FIX(2), '*', s));
		s = rb_funcall(t, div, 2, INT2FIX(3), prec);
	} while (RTEST(rb_num_coerce_cmp(s, prev, '<')));
	RB_GC_GUARD(s);
	RB_GC_GUARD(t);
	RB_GC_GUARD(prev);
	return positive ? prev : rb_num_uminus(prev);
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
powerroot_math_cuberoot(VALUE unused_obj, VALUE x, VALUE prec)
{
	return rb_bigmath_cuberoot(x, prec);
}


/**
 * ```Ruby
 * def ccbrt(z, prec)
 *   log = BigMathR::LogSqrt.clog(z, prec)
 *   BigMathR::TrigExp.cexp(1/3r * log, prec)
 * end
 * ```
 */
static VALUE
rb_bigmath_ccbrt(VALUE z, VALUE prec)
{
	VALUE log = Qundef, one_third = rb_Rational(INT2FIX(1), INT2FIX(3));
	rb_check_precise(prec);
	log = rb_bigmath_clog(z, prec);
	log = rb_funcall1(one_third, '*', log);
	return rb_bigmath_cexp(log, prec);
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
powerroot_math_ccbrt(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
        return rb_bigmath_ccbrt(z, prec);
}

/**
 *  Document-module:  BigMathR::PowerRoot
 *  
 *  A module that provides the power-root functions. 
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
InitVM_PowerRoot(void)
{
	rb_define_module_function(rb_mPowerRoot, "sqrt", powerroot_math_sqrt, 2);
	rb_define_module_function(rb_mPowerRoot, "csqrt", powerroot_math_csqrt, 2);
	rb_define_module_function(rb_mPowerRoot, "cuberoot", powerroot_math_cuberoot, 2);
	rb_define_module_function(rb_mPowerRoot, "ccbrt", powerroot_math_ccbrt, 2);
}
