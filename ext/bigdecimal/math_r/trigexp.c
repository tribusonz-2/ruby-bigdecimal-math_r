/*******************************************************************************
	trigexp.c -- Trigonometry & Exponent (Euler's formula)

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "internal/solver/bigmath_r.h"

static VALUE
f_euler(VALUE theta, VALUE prec)
{
	VALUE sin, cos, pi, t, y;
	if (!rb_num_finite_p(theta))
		return rb_Complex(BIG_NAN, BIG_NAN);
	pi = rb_bigmath_pi(prec);
	y = rb_sincos_to_radian(theta, prec, pi, &t);
	if (rb_degree_sparg(t, prec, &sin, &cos) == -1)
		rb_bigmath_sincos(y, prec, &sin, &cos);
	return rb_Complex(cos, sin);
}

static void
f_euler2(VALUE theta, VALUE prec, VALUE *exppz, VALUE *expmz)
{
	const ID conj = rb_intern("conj");
	*exppz = f_euler(rb_num_imag(theta), prec);
	*expmz = rb_funcall(*exppz, conj, 0);
}

static VALUE
f_euler_e(VALUE z, VALUE prec)
{
	const ID mult = rb_intern("mult");
	VALUE theta, r;
	if (!rb_num_finite_p(rb_num_imag(z)))
		return rb_Complex(BIG_NAN, BIG_NAN);
	r = rb_bigmath_canonicalize(rb_num_real(z), prec, ARG_REAL, ARG_RAWVALUE);
	r = rb_bigmath_exp(r, prec);
	if (rb_num_notequal_p(r, r))
		return rb_Complex(BIG_NAN, BIG_NAN);
	theta = f_euler(rb_num_imag(z), prec);
	return rb_Complex(
		rb_funcall(rb_BigDecimal1(r), mult, 2, rb_num_real(theta), prec),
		rb_funcall(rb_BigDecimal1(r), mult, 2, rb_num_imag(theta), prec)
	);
}

static void
f_euler_e2(VALUE theta, VALUE prec, VALUE *exppz, VALUE *expmz)
{
	const ID div = rb_intern("div");
	VALUE r = rb_num_real(theta);
	r = rb_bigmath_canonicalize(r, prec, ARG_REAL, ARG_RAWVALUE);
	r = rb_bigmath_exp(r, prec);
	if (rb_num_notequal_p(r, r))
	{
		*exppz = BIG_NAN;
		*expmz = BIG_NAN;
	}
	else if (TYPE(r) == T_FIXNUM || TYPE(r) == T_BIGNUM)
	{
		*exppz = rb_BigDecimal1(r);
		r = rb_Rational(INT2FIX(1), r);
		*expmz = rb_BigDecimal(r, prec);
	}
	else
	{
		*exppz = rb_BigDecimal1(r);
		r = rb_funcall(BIG_ONE, div, 2, r, prec);
		*expmz = rb_BigDecimal1(r);
	}
}


static VALUE
f_euler_cos(VALUE exppz, VALUE expmz)
{
	VALUE y = rb_funcall1(exppz, '+', expmz);
	y = rb_funcall1(y, '/', INT2FIX(2));
	if (rb_num_real_p(y))
		y = rb_Complex(y, BIG_ZERO);
	return y;
}

static VALUE
f_euler_sin_infinite(VALUE y)
{
	VALUE w = Qundef;
	int real_sign, imag_sign;
	real_sign = rb_num_infinite_p(rb_num_real(y));
	imag_sign = rb_num_infinite_p(rb_num_imag(y));
	if (real_sign == 1)
	{
		VALUE imag = rb_num_imag(y);
		if (rb_num_zero_p(imag))
			w = rb_Complex(BIG_ZERO, BIG_MINUS_INF);
		else if (rb_num_positive_p(imag))
			w = rb_Complex(BIG_MINUS_INF, BIG_INF);
		else if (rb_num_negative_p(imag))
			w = rb_Complex(BIG_INF, BIG_INF);
	}
	else if (real_sign == -1)
	{
		VALUE imag = rb_num_imag(y);
		if (rb_num_zero_p(imag))
			w = rb_Complex(BIG_ZERO, BIG_INF);
		else if (rb_num_positive_p(imag))
			w = rb_Complex(BIG_INF, BIG_INF);
		else if (rb_num_negative_p(imag))
			w = rb_Complex(BIG_MINUS_INF, BIG_INF);
	}
	else if (imag_sign == 1)
	{
		VALUE real = rb_num_real(y);
		if (rb_num_zero_p(real))
			w = rb_Complex(BIG_INF, BIG_ZERO);
		else if (rb_num_positive_p(real))
			w = rb_Complex(BIG_MINUS_INF, BIG_INF);
		else if (rb_num_negative_p(real))
			w = rb_Complex(BIG_INF, BIG_INF);
	}
	else if (imag_sign == -1)
	{
		VALUE real = rb_num_real(y);
		if (rb_num_zero_p(real))
			w = rb_Complex(BIG_MINUS_INF, BIG_ZERO);
		else if (rb_num_positive_p(real))
			w = rb_Complex(BIG_MINUS_INF, BIG_MINUS_INF);
		else if (rb_num_negative_p(real))
			w = rb_Complex(BIG_MINUS_INF, BIG_INF);
	}
	
	if (w == Qundef)
		rb_raise(rb_eRuntimeError, "no solution (in f_euler_sin_infinite())");
	return w;
}

static VALUE
f_euler_sin(VALUE exppz, VALUE expmz)
{
	VALUE y = rb_funcall1(exppz, '-', expmz);
	VALUE two_i = rb_Complex(BIG_ZERO, rb_BigDecimal1(INT2FIX(2)));
	// BUG: In the current version 3.3.5
	// -Float::INFINITY / 2i #=> (NaN+Infinity*i)
	// Correct: (0.0+Infinity*i)
	if (!rb_num_finite_p(y))
		y = f_euler_sin_infinite(y);
	else
		y = rb_funcall1(y, '/', two_i);
	return y;
}

static VALUE
f_euler_tan(VALUE exppz, VALUE expmz)
{
	VALUE sin, cos;

	if (rb_num_zero_p(exppz))
		return rb_Complex(BIG_ZERO, BIG_ONE);
	else if (rb_num_infinite_p(exppz))
		return rb_Complex(BIG_ZERO, BIG_MINUS_ONE);
	/* else */
	sin = rb_funcall1(expmz, '-', exppz);
	sin = rb_ImaginaryZ(sin, SIGN_PLUS);
	cos = rb_funcall1(expmz, '+', exppz);
	return rb_funcall1(sin, '/', cos);
}

static VALUE
f_euler_sc(const ID func, VALUE theta, VALUE prec)
{
	const ID sin = rb_intern("sin");
	const ID cos = rb_intern("cos");
	const ID tan = rb_intern("tan");
	VALUE exppz = Qundef, expmz = Qundef, y = Qundef;

	RUBY_ASSERT(func != sin);
	RUBY_ASSERT(func != cos);
	RUBY_ASSERT(func != tan);

	if (!rb_num_finite_p(rb_num_imag(theta)))
		return rb_Complex(BIG_NAN, BIG_NAN);

	f_euler2(theta, prec, &exppz, &expmz);

	if (func == cos)
	{
		y = f_euler_cos(exppz, expmz);
	}
	else if (func == sin)
	{
		y = f_euler_sin(exppz, expmz);
	}
	else if (func == tan)
	{
		y = f_euler_tan(exppz, expmz);
	}
	return rb_bigmath_round_inline(y, prec);
}

// For real of tangent's exponent, tanh(x), coth(x) or tan(i x) or cot(i x)
static VALUE
f_euler_t(VALUE theta, VALUE prec)
{
	const ID div = rb_intern("div");
	const ID sub = rb_intern("sub");
	const ID add = rb_intern("add");
	const ID pred = rb_intern("pred");
	const ID succ = rb_intern("succ");
	VALUE y = Qundef;
	theta = rb_num_real(theta);
	theta = rb_bigmath_canonicalize(theta, prec, ARG_REAL, ARG_RAWVALUE);
	if (!rb_num_finite_p(theta))
	{
		switch (NUM2INT(rb_BigDecimal_sign(theta))) {
		case 0:
			y = BIG_NAN;
			break;
		case 3:
			y = BIG_ONE;
			break;
		case -3:
			y = BIG_MINUS_ONE;
			break;
		}
	}
	else
	{
		y = rb_bigmath_exp(rb_funcall(INT2FIX(2), '*', 1, rb_num_real(theta)), prec);
		if (CLASS_OF(y) == rb_cBigDecimal)
		{
			if (rb_num_finite_p(y))
				y = rb_funcall(
					rb_funcall(y, sub, 2, INT2FIX(1), prec), div, 2,
					rb_funcall(y, add, 2, INT2FIX(1), prec), prec
				    );
			else if (rb_num_infinite_p(y))
				y = BIG_ONE;
		}
		else if (TYPE(y) == T_FIXNUM || TYPE(y) == T_BIGNUM)
		{
			y = rb_BigDecimal(
				rb_Rational(
					rb_funcall(y, pred, 0),
					rb_funcall(y, succ, 0)
				), prec);
		}
		else
			y = BIG_ONE;
	}
	if (y == Qundef)
		rb_raise(rb_eRuntimeError, "no solution");
	return rb_ImaginaryZ(y, SIGN_MINUS);
}


static VALUE
f_euler_h(const ID func, VALUE theta, VALUE prec)
{
	const ID sin = rb_intern("sin");
	const ID cos = rb_intern("cos");
	const ID tan = rb_intern("tan");
	VALUE y = Qundef, exppz = Qundef, expmz = Qundef;
	RUBY_ASSERT(func != sin);
	RUBY_ASSERT(func != cos);
	RUBY_ASSERT(func != tan);

	if (func == tan)
		return f_euler_t(theta, prec);
	
	f_euler_e2(rb_num_real(theta), prec, &exppz, &expmz);

	if (func == cos)
	{
		y = f_euler_cos(exppz, expmz);
	}
	else if (func == sin)
	{
		y = f_euler_sin(exppz, expmz);
	}
	return rb_bigmath_round_inline(y, prec);
}

static VALUE
f_euler_esc(ID func, VALUE z, VALUE prec)
{
	const ID sin = rb_intern("sin");
	const ID cos = rb_intern("cos");
	const ID tan = rb_intern("tan");
	VALUE e_exppz  = Qundef,
	      e_expmz  = Qundef,
	      sc_exppz = Qundef,
	      sc_expmz = Qundef,
	      exppz    = Qundef,
	      expmz    = Qundef,
	      y        = Qundef;
	f_euler_e2(z, prec, &e_exppz, &e_expmz);
	f_euler2(z, prec, &sc_exppz, &sc_expmz);
	exppz = rb_funcall1(e_exppz, '*', sc_exppz);
	expmz = rb_funcall1(e_expmz, '*', sc_expmz);
	
	if (func == cos)
	{
		y = f_euler_cos(exppz, expmz);
	}
	else if (func == sin)
	{
		y = f_euler_sin(exppz, expmz);
	}
	else if (func == tan)
	{
		y = f_euler_tan(exppz, expmz);
	}
	return rb_bigmath_round_inline(y, prec);
}


static VALUE
f_euler_trig(ID func, VALUE theta, VALUE prec)
{
	VALUE h = Qundef, sc = Qundef;
	RUBY_ASSERT(func != sin);
	RUBY_ASSERT(func != cos);
	RUBY_ASSERT(func != tan);
	if (rb_num_nan_p(theta))
		return rb_Complex(BIG_NAN, BIG_NAN);
	if (rb_num_zero_p(rb_num_imag(theta)))
	{
		h = f_euler_h(func, theta, prec);
		if (rb_num_nan_p(h))
			return h;
	}
	if (rb_num_zero_p(rb_num_real(theta)))
	{
		sc = f_euler_sc(func, theta, prec);
		if (rb_num_nan_p(sc))
			return sc;
	}
	if (h != Qundef && sc == Qundef)
		return h;
	else if (h == Qundef && sc != Qundef)
		return sc;
	else
	{
		VALUE y = f_euler_esc(func, theta, prec);
		return y;
	}
}


/**
 *  ```Ruby
 *  def cexp(z, prec)
 *    f_euler_e(z, prec)
 *  end
 *  ```
 */
VALUE
rb_bigmath_cexp(VALUE z, VALUE prec)
{
	rb_check_precise(prec);
	return f_euler_e(z, prec);
}

/**
 * Computes complex exponential function of +z+.
 * 
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.cexp(1+1i, 20)
 *  #=> (0.14686939399158851572e1+0.22873552871788423912e1i)
 * @since 0.1.0
 */
static VALUE
trigexp_math_cexp(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_bigmath_cexp(z, prec);
}

/**
 * Computes complex binary exponent of +z+.
 * 
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.cexp2(1+1i, 20)
 *  #=> (0.15384778027279442532e1+0.12779225526272696023e1i)
 * @since 0.1.0
 */
static VALUE
trigexp_math_cexp2(VALUE unused_obj, VALUE z, VALUE prec)
{
	VALUE log2 = rb_bigmath_const_log2(prec);
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	z = rb_funcall1(z, '*', log2);
	return rb_bigmath_cexp(z, prec);
}


/**
 *  ```Ruby
 *  def csin(z, prec)
 *    f_euler_sc(:sin, Complex::I * z, prec)
 *  end
 *  ```
 */
static VALUE
rb_bigmath_csin(VALUE z, VALUE prec)
{
	const ID sin = rb_intern("sin");
	return f_euler_trig(sin, rb_ImaginaryZ(z, SIGN_PLUS), prec);
}


/**
 * Computes complex sine of +z+.
 * 
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.csin(1+1i, 20)
 *  #=> (0.12984575814159772948e1+0.63496391478473610827e0i)
 * @since 0.1.0
 */
static VALUE
trigexp_math_csin(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_bigmath_csin(z, prec);
}


/**
 *  ```Ruby
 *  def ccos(z, prec)
 *    f_euler_trig(:cos, Complex::I * z, prec)
 *  end
 *  ```
 */
static VALUE
rb_bigmath_ccos(VALUE z, VALUE prec)
{
	const ID cos = rb_intern("cos");
	return f_euler_trig(cos, rb_ImaginaryZ(z, SIGN_PLUS), prec);
}

/**
 * Computes complex cosine of +z+.
 * 
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.ccos(1+1i, 20)
 *  #=> (0.83373002513114904889e0-0.9888977057628650964e0i)
 * @since 0.1.0
 */
static VALUE
trigexp_math_ccos(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_bigmath_ccos(z, prec);
}


/**
 *  ```Ruby
 *  def ctan(z, prec)
 *    
 f_euler_trig(:tan, Complex::I * z, prec)
 *  end
 *  ```
 */
static VALUE
rb_bigmath_ctan(VALUE z, VALUE prec)
{
	const ID tan = rb_intern("tan");
	return f_euler_trig(tan, rb_ImaginaryZ(z, SIGN_PLUS), prec);
}

/**
 * Computes complex tangent of +z+.
 * 
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.ctan(1+1i, 20)
 *  #=> (0.27175258531951171652e0+0.10839233273386945435e1i)
 * @since 0.1.0
 */
static VALUE
trigexp_math_ctan(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_bigmath_ctan(z, prec);
}


/**
 *  ```Ruby
 *  def ccsc(z, prec)
 *    w = f_euler_trig(:sin, Complex::I * z, prec)
 *    Complex(*w.rect.map{|x| BigDecimal(1).div(x, prec)})
 *  end
 *  ```
 */
static VALUE
rb_bigmath_ccsc(VALUE z, VALUE prec)
{
	const ID sin = rb_intern("sin");
	VALUE w = f_euler_trig(sin, rb_ImaginaryZ(z, SIGN_PLUS), prec);
	return rb_bigmath_canonicalize(w, prec, ARG_COMPLEX, ARG_RECIPROCAL);
}

/**
 * Computes complex cosecant of +z+.
 * 
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.ccsc(1+1i, 20)
 *  #=> (0.62151801717042842124e0-0.30393100162842645035e0i)
 * @since 0.1.0
 */
static VALUE
trigexp_math_ccsc(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_bigmath_ccsc(z, prec);
}


/**
 *  ```Ruby
 *  def csec(z, prec)
 *    w = f_euler_trig(:cos, Complex::I * z, prec).real
 *    Complex(*w.rect.map{|x| BigDecimal(1).div(x, prec)})
 *  end
 *  ```
 */
static VALUE
rb_bigmath_csec(VALUE z, VALUE prec)
{
	const ID cos = rb_intern("cos");
	VALUE w = f_euler_trig(cos, rb_ImaginaryZ(z, SIGN_PLUS), prec);
	return rb_bigmath_canonicalize(w, prec, ARG_COMPLEX, ARG_RECIPROCAL);
}

/**
 * Computes complex secant of +z+.
 * 
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.csec(1+1i, 20)
 *  #=> (0.4983370305551867852e0+0.59108384172104504804e0i)
 * @since 0.1.0
 */
static VALUE
trigexp_math_csec(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_bigmath_csec(z, prec);
}


/**
 *  ```Ruby
 *  def ccot(z, prec)
 *    w = f_euler_trig(:tan, Complex::I * z, prec).real
 *    Complex(*w.rect.map{|x| BigDecimal(1).div(x, prec)})
 *  end
 *  ```
 */
static VALUE
rb_bigmath_ccot(VALUE z, VALUE prec)
{
	const ID tan = rb_intern("tan");
	VALUE w = f_euler_trig(tan, rb_ImaginaryZ(z, SIGN_PLUS), prec);
	return rb_bigmath_canonicalize(w, prec, ARG_COMPLEX, ARG_RECIPROCAL);
}

/**
 * Computes complex cotangent of +z+.
 * 
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.ctan(1+1i, 20)
 *  #=> (0.21762156185440268135e0-0.86801414289592494862e0i)
 * @since 0.1.0
 */
static VALUE
trigexp_math_ccot(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_bigmath_ccot(z, prec);
}

/**
 *  ```Ruby
 *  def sinh(x, prec)
 *    raise TypeError, "no solution for Complex" if !x.imag.zero?
 *    (Complex::I * f_euler_trig(:sin, x, prec)).real
 *  end
 *  ```
 */
static VALUE
rb_bigmath_sinh(VALUE x, VALUE prec)
{
	const ID sin = rb_intern("sin");
	VALUE y;
	y = rb_ImaginaryZ(f_euler_trig(sin, x, prec), SIGN_PLUS);
	return rb_num_real(y);
}

/**
 * Computes hyperbolic sine of +x+.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.sinh(1, 20)
 *  #=> 0.11752011936438014569e1
 * @since 0.1.0
 */
static VALUE
trigexp_math_sinh(VALUE unused_obj, VALUE x, VALUE prec)
{
	x = rb_bigmath_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_bigmath_sinh(x, prec);
}

/**
 *  ```Ruby
 *  def cosh(x, prec)
 *    raise TypeError, "no solution for Complex" if !x.imag.zero?
 *    f_euler_trig(:cos, x, prec).real
 *  end
 *  ```
 */
static VALUE
rb_bigmath_cosh(VALUE x, VALUE prec)
{
	const ID cos = rb_intern("cos");
	VALUE y;
	y = f_euler_trig(cos, x, prec);
	return rb_num_real(y);
}

/**
 * Computes hyperbolic cosine of +x+.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.cosh(1, 20)
 *  #=> 0.15430806348152437785e1
 * @since 0.1.0
 */
static VALUE
trigexp_math_cosh(VALUE unused_obj, VALUE x, VALUE prec)
{
	x = rb_bigmath_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_bigmath_cosh(x, prec);
}


/**
 *  ```Ruby
 *  def tanh(x, prec)
 *    raise TypeError, "no solution for Complex" if !x.imag.zero?
 *    (Complex::I * f_euler_trig(:tan, x, prec)).real
 *  end
 *  ```
 */
static VALUE
rb_bigmath_tanh(VALUE x, VALUE prec)
{
	const ID tan = rb_intern("tan");
	VALUE y;
	y = rb_ImaginaryZ(f_euler_trig(tan, x, prec), SIGN_PLUS);
	return rb_num_real(y);
}

/**
 * Computes hyperbolic tangent of +x+.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.tanh(1, 20)
 *  #=> 0.76159415595576488813e0
 * @since 0.1.0
 */
static VALUE
trigexp_math_tanh(VALUE unused_obj, VALUE x, VALUE prec)
{
	x = rb_bigmath_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_bigmath_tanh(x, prec);
}


/**
 *  ```Ruby
 *  def csch(x, prec)
 *    raise TypeError, "no solution for Complex" if !x.imag.zero?
 *    y = Complex::I * f_euler_trig(:sin, x, prec).real
 *    (BigDecimal(1).div(y, prec)).real
 *  end
 *  ```
 */
static VALUE
rb_bigmath_csch(VALUE x, VALUE prec)
{
	const ID sin = rb_intern("sin");
	VALUE y;
	y = rb_ImaginaryZ(f_euler_trig(sin, x, prec), SIGN_PLUS);
	return rb_bigmath_canonicalize(y, prec, ARG_REAL, ARG_RECIPROCAL);
}

/**
 * Computes hyperbolic cosecant of +x+.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.csch(1, 20)
 *  #=> 0.85091812823932154512e0
 * @since 0.1.0
 */
static VALUE
trigexp_math_csch(VALUE unused_obj, VALUE x, VALUE prec)
{
	x = rb_bigmath_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_bigmath_csch(x, prec);
}


/**
 *  ```Ruby
 *  def sech(x, prec)
 *    raise TypeError, "no solution for Complex" if !x.imag.zero?
 *    y = f_euler_trig(:cos, x, prec).real
 *    (BigDecimal(1).div(y, prec)).real
 *  end
 *  ```
 */
static VALUE
rb_bigmath_sech(VALUE x, VALUE prec)
{
	const ID cos = rb_intern("cos");
	VALUE y;
	y = f_euler_trig(cos, x, prec);
	return rb_bigmath_canonicalize(y, prec, ARG_REAL, ARG_RECIPROCAL);
}

/**
 * Computes hyperbolic secant of +x+.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.sech(1, 20)
 *  #=> 0.64805427366388539957e0
 * @since 0.1.0
 */
static VALUE
trigexp_math_sech(VALUE unused_obj, VALUE x, VALUE prec)
{
	x = rb_bigmath_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_bigmath_sech(x, prec);
}


/**
 *  ```Ruby
 *  def coth(x, prec)
 *    raise TypeError, "no solution for Complex" if !x.imag.zero?
 *    y = Complex::I * f_euler_trig(:tan, x, prec).real
 *    (BigDecimal(1).div(y, prec)).real
 *  end
 *  ```
 */
static VALUE
rb_bigmath_coth(VALUE x, VALUE prec)
{
	const ID tan = rb_intern("tan");
	VALUE y;
	y = rb_ImaginaryZ(f_euler_trig(tan, x, prec), SIGN_PLUS);
	return rb_bigmath_canonicalize(y, prec, ARG_REAL, ARG_RECIPROCAL);
}

/**
 * Computes hyperbolic cotangent of +x+.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.coth(1, 20)
 *  #=> 0.13130352854993313036e1
 * @since 0.1.0
 */
static VALUE
trigexp_math_coth(VALUE unused_obj, VALUE x, VALUE prec)
{
	x = rb_bigmath_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_bigmath_coth(x, prec);
}


/**
 *  ```Ruby
 *  def csinh(z, prec)
 *    Complex::I * f_euler_trig(:sin, z, prec)
 *  end
 *  ```
 */
static VALUE
rb_bigmath_csinh(VALUE z, VALUE prec)
{
	const ID sin = rb_intern("sin");
	return rb_ImaginaryZ(f_euler_trig(sin, z, prec), SIGN_PLUS);
}

/**
 * Computes complex hyperbolic sine of +z+.
 * 
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.csinh(1+1i, 20)
 *  #=> (0.63496391478473610827e0+0.12984575814159772948e1i)
 * @since 0.1.0
 */
static VALUE
trigexp_math_csinh(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_bigmath_csinh(z, prec);
}


/**
 *  ```Ruby
 *  def ccosh(z, prec)
 *    f_euler_trig(:cos, z, prec)
 *  end
 *  ```
 */
static VALUE
rb_bigmath_ccosh(VALUE z, VALUE prec)
{
	const ID cos = rb_intern("cos");
	return f_euler_trig(cos, z, prec);
}

/**
 * Computes complex hyperbolic cosine of +z+.
 * 
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.ccosh(1+1i, 20)
 *  #=> (0.83373002513114904889e0+0.9888977057628650964e0i)
 * @since 0.1.0
 */
static VALUE
trigexp_math_ccosh(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_bigmath_ccosh(z, prec);
}


/**
 *  ```Ruby
 *  def ctanh(z, prec)
 *    Complex::I * f_euler_trig(:tan, z, prec)
 *  end
 *  ```
 */
static VALUE
rb_bigmath_ctanh(VALUE z, VALUE prec)
{
	const ID tan = rb_intern("tan");
	return rb_ImaginaryZ(f_euler_trig(tan, z, prec), SIGN_PLUS);
}

/**
 * Computes complex hyperbolic tangent of +z+.
 * 
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.ctanh(1+1i, 20)
 *  #=> (0.10839233273386945435e1+0.27175258531951171652e0i)
 * @since 0.1.0
 */
static VALUE
trigexp_math_ctanh(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_bigmath_ctanh(z, prec);
}

/**
 *  ```Ruby
 *  def ccsch(z, prec)
 *    w = Complex::I * f_euler_trig(:sin, z, prec)
 *    Complex(*w.rect.map{|x| BigDecimal(1).div(x, prec)})
 *  end
 *  ```
 */
static VALUE
rb_bigmath_ccsch(VALUE z, VALUE prec)
{
	const ID sin = rb_intern("sin");
	VALUE w = rb_ImaginaryZ(f_euler_trig(sin, z, prec), SIGN_PLUS);
	return rb_bigmath_canonicalize(w, prec, ARG_COMPLEX, ARG_RECIPROCAL);
}

/**
 * Computes complex hyperbolic cosecant of +z+.
 * 
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.ccsch(1+1i, 20)
 *  #=> (0.30393100162842645035e0-0.62151801717042842124e0i)
 * @since 0.1.0
 */
static VALUE
trigexp_math_ccsch(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_bigmath_ccsch(z, prec);
}


/**
 *  ```Ruby
 *  def csech(z, prec)
 *    w = f_euler_trig(:cos, z, prec)
 *    Complex(*w.rect.map{|x| BigDecimal(1).div(x, prec)})
 *  end
 *  ```
 */
static VALUE
rb_bigmath_csech(VALUE z, VALUE prec)
{
	const ID cos = rb_intern("cos");
	VALUE w = f_euler_trig(cos, z, prec);
	return rb_bigmath_canonicalize(w, prec, ARG_COMPLEX, ARG_RECIPROCAL);
}

/**
 * Computes complex hyperbolic secant of +z+.
 * 
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.csech(1+1i, 20)
 *  #=> (0.4983370305551867852e0-0.59108384172104504804e0i)
 * @since 0.1.0
 */
static VALUE
trigexp_math_csech(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_bigmath_csech(z, prec);
}


/**
 *  ```Ruby
 *  def ccoth(z, prec)
 *    w = Complex::I * f_euler_trig(:tan, z, prec)
 *    Complex(*w.rect.map{|x| BigDecimal(1).div(x, prec)})
 *  end
 *  ```
 */
static VALUE
rb_bigmath_ccoth(VALUE z, VALUE prec)
{
	const ID tan = rb_intern("tan");
	VALUE w = rb_ImaginaryZ(f_euler_trig(tan, z, prec), SIGN_PLUS);
	return rb_bigmath_canonicalize(w, prec, ARG_COMPLEX, ARG_RECIPROCAL);
}

/**
 * Computes complex hyperbolic cotangent of +z+.
 * 
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.ccoth(1+1i, 20)
 *  #=> (0.86801414289592494862e0-0.21762156185440268135e0i)
 * @since 0.1.0
 */
static VALUE
trigexp_math_ccoth(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_bigmath_ccoth(z, prec);
}


/**
 *  Document-module:  BigMathR::TrigExp
 *  
 *  A module that provides using trigonometric and exponential function. 
 *  It is used internally.
 *  <br>
 *  "TrigExp" is, simply put, a module that uses Euler's formula.
 *  <br>
 *  By using this formula for complex analysis, 
 *  it can be applied to differential equations and Fourier transforms.
 *  <br>
 *  <br>
 *  The function names defined are the same as those in the C/C++ standard.
 *  <br>
 *  Exponential function:         +cexp()+ <br>
 *  Base-2 (Binary) exponent:     +cexp2()+ <br>
 *  Sine:                         +csin()+ <br>
 *  Cosine:                       +ccos()+ <br>
 *  Tangent:                      +ctan()+ <br>
 *  Hyperbolic sine:     +sinh()+ +csinh()+ <br>
 *  Hyperbolic cosine:   +cosh()+ +ccosh()+ <br>
 *  Hyperbolic tangent:  +tanh()+ +ctanh()+ <br>
 *  Follow, those reciprocals of not defined in C/C++ standard.
 *  <br>
 *  Cosecant:                     +ccsc()+ <br>
 *  Secant:                       +csec()+ <br>
 *  Cotangent:                    +ccot()+ <br>
 *  Hyperbolic cosecant  +csch()+ +ccsch()+ <br>
 *  Hyperbolic secant:   +sech()+ +csech()+ <br>
 *  Hyperbolic cotangent +coth()+ +ccoth()+ <br>
 */
void
InitVM_TrigExp(void)
{
	rb_define_module_function(rb_mTrigExp, "cexp", trigexp_math_cexp, 2);
	rb_define_module_function(rb_mTrigExp, "cexp2", trigexp_math_cexp2, 2);

	rb_define_module_function(rb_mTrigExp, "csin", trigexp_math_csin, 2);
	rb_define_module_function(rb_mTrigExp, "ccos", trigexp_math_ccos, 2);
	rb_define_module_function(rb_mTrigExp, "ctan", trigexp_math_ctan, 2);
	rb_define_module_function(rb_mTrigExp, "ccsc", trigexp_math_ccsc, 2);
	rb_define_module_function(rb_mTrigExp, "csec", trigexp_math_csec, 2);
	rb_define_module_function(rb_mTrigExp, "ccot", trigexp_math_ccot, 2);

	rb_define_module_function(rb_mTrigExp, "sinh", trigexp_math_sinh, 2);
	rb_define_module_function(rb_mTrigExp, "cosh", trigexp_math_cosh, 2);
	rb_define_module_function(rb_mTrigExp, "tanh", trigexp_math_tanh, 2);
	rb_define_module_function(rb_mTrigExp, "csch", trigexp_math_csch, 2);
	rb_define_module_function(rb_mTrigExp, "sech", trigexp_math_sech, 2);
	rb_define_module_function(rb_mTrigExp, "coth", trigexp_math_coth, 2);

	rb_define_module_function(rb_mTrigExp, "csinh", trigexp_math_csinh, 2);
	rb_define_module_function(rb_mTrigExp, "ccosh", trigexp_math_ccosh, 2);
	rb_define_module_function(rb_mTrigExp, "ctanh", trigexp_math_ctanh, 2);
	rb_define_module_function(rb_mTrigExp, "ccsch", trigexp_math_ccsch, 2);
	rb_define_module_function(rb_mTrigExp, "csech", trigexp_math_csech, 2);
	rb_define_module_function(rb_mTrigExp, "ccoth", trigexp_math_ccoth, 2);
}
