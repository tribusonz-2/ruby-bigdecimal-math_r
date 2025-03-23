/*******************************************************************************
	nucomp.c -- Complex Plane

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "internal/solver/bigmath_r.h"

static VALUE
bigflo_sqrt(VALUE x, VALUE prec)
{
	const ID sqrt = rb_intern("sqrt");
	const ID round = rb_intern("round");
	x = rb_funcall(x, sqrt, 1, prec);
	return rb_funcall(x, round, 1, prec);
}

static VALUE
l2norm_iter(RB_BLOCK_CALL_FUNC_ARGLIST(y, c))
{
	const ID abs2 = rb_intern("abs2");
	return rb_funcall(y, abs2, 0);
}

static VALUE
l2norm_sum(VALUE self)
{
	const ID sum = rb_intern("sum");
	return rb_block_call(self, sum, 0, NULL, l2norm_iter, Qnil);
}

static VALUE
num_l2norm(VALUE vec, VALUE prec)
{
	VALUE sum;
	if (CLASS_OF(vec) != rb_cArray)
		rb_raise(rb_eTypeError, "vec must be an Array");

	sum = l2norm_sum(vec);

	switch (TYPE(sum)) {
	case T_FIXNUM:
	case T_BIGNUM:
		sum = rb_BigDecimal1(sum);
		break;
	case T_FLOAT:
		sum = rb_BigDecimal_flo(sum);
		break;
	case T_RATIONAL:
		sum = rb_BigDecimal(sum, prec);
		break;
	default:
		break;
	}
	return bigflo_sqrt(sum, prec);
}

VALUE
rb_bigmath_l2norm(VALUE vec, VALUE prec)
{
	return num_l2norm(vec, prec);
}


static VALUE
nucomp_l2norm(VALUE unused_obj, VALUE args)
{
	if (RARRAY_LEN(args) < 2)
		rb_raise(rb_eArgError, 
			"wrong number of arguments (given %ld, expected 2..)", 
			RARRAY_LEN(args));
	VALUE prec = rb_ary_pop(args);
	rb_check_precise(prec);
	return num_l2norm(args, prec);
}


VALUE
rb_bigmath_hypot(VALUE a, VALUE b, VALUE prec)
{
	rb_check_precise(prec);
	return num_l2norm(rb_assoc_new(a, b), prec);
}


/**
 *  Returns the hypotenuse of a right triangle with side lengths of +a+ and +b+.
 *  <br>
 *  The return value will definitely be a positive real number. 
 *  <br>
 *  It is implemented by the norm, 
 *  so even if the argument is a complex number, 
 *  it will be a positive real number.
 *  
 *  @param a [Numeric] adjacent side or opposite side
 *  @param b [Numeric] adjacent side or opposite side
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +x+ is not a numeric class.
 *  @since 0.1.0
 */
static VALUE
nucomp_math_hypot(VALUE unused_obj, VALUE a, VALUE b, VALUE prec)
{
	a = rb_bigmath_canonicalize(a, prec, ARG_REAL, ARG_RAWVALUE);
	b = rb_bigmath_canonicalize(b, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_bigmath_hypot(a, b, prec);
}


VALUE
rb_bigmath_cabs(VALUE z, VALUE prec)
{
	rb_check_precise(prec);
	return num_l2norm(rb_assoc_new(rb_num_real(z), rb_num_imag(z)), prec);
}


static VALUE
nucomp_cabs(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_bigmath_cabs(z, prec);
}

/**
 * 
 *  ```Ruby
 *  PREC = 20
 *  # Quadrant XY in non-finites
 *  # For 0-deg
 *  ComplexPlane.quadrant(-1.0, BigDecimal::INFINITY, PREC)   #=> -0.0
 *  ComplexPlane.quadrant(1.0, BigDecimal::INFINITY, PREC)  #=> 0.0
 *  ComplexPlane.quadrant(-0.0, BigDecimal::INFINITY, PREC) #=> -0.0
 *  ComplexPlane.quadrant(BigDecimal('-0'), BigDecimal::INFINITY, PREC) #=> -0.0
 *  ComplexPlane.quadrant(0.0, BigDecimal::INFINITY, PREC) #=> 0.0
 *  ComplexPlane.quadrant(BigDecimal('0'), BigDecimal::INFINITY, PREC) #=> 0.0
 *  # For 45-Deg
 *  ComplexPlane.quadrant(BigDecimal::INFINITY, BigDecimal::INFINITY, PREC) #=> 0.78539816339744830962e0
 *  # For 90-Deg
 *  ComplexPlane.quadrant(BigDecimal::INFINITY, 0.0, PREC) #=> 0.15707963267948966192e1
 *  # For 135-Deg
 *  ComplexPlane.quadrant(BigDecimal::INFINITY, -BigDecimal::INFINITY, PREC) #=> -0.78539816339744830962e0
 *  # For 180-deg
 *  ComplexPlane.quadrant(-1.0, -BigDecimal::INFINITY, PREC) #=> -0.31415926535897932385e1
 *  ComplexPlane.quadrant(1.0, -BigDecimal::INFINITY, PREC) #=> 0.31415926535897932385e1
 *  ComplexPlane.quadrant(-0.0, -BigDecimal::INFINITY, PREC) #=0> -0.31415926535897932385e1
 *  ComplexPlane.quadrant(BigDecimal('-0'), -BigDecimal::INFINITY, PREC) #=> -0.31415926535897932385e1
 *  ComplexPlane.quadrant(0.0, -BigDecimal::INFINITY, PREC) #=> 0.31415926535897932385e1
 *  ComplexPlane.quadrant(BigDecimal('0'), -BigDecimal::INFINITY, PREC) #=> 0.31415926535897932385e1
 *  # For 225-Deg
 *  ComplexPlane.quadrant(-BigDecimal::INFINITY, -BigDecimal::INFINITY, PREC) #=> -0.23561944901923449288e1
 *  # For 270-Deg
 *  ComplexPlane.quadrant(-BigDecimal::INFINITY, 0.0, PREC) #=> -0.15707963267948966192e1
 *  # For 315-Deg
 *  ComplexPlane.quadrant(-BigDecimal::INFINITY, BigDecimal::INFINITY, PREC) #=> 0.23561944901923449288e1
 *  
 *  # Quadrant XY in the complex argument
 *  ComplexPlane.quadrant(0.0, 0.0, PREC) #=> 0.0
 *  ComplexPlane.quadrant(0.0, -0.0, PREC) #=> -0.0
 *  ComplexPlane.quadrant(-0.0, -0.0, PREC) #=> -0.31415926535897932385e1
 *  ComplexPlane.quadrant(-0.0, 0.0, PREC) #=> 0.31415926535897932385e1
 *  ComplexPlane.quadrant(0.0, rand(), PREC) #=> 0.15707963267948966192e1
 *  ComplexPlane.quadrant(0.0, -rand(), PREC) #=> -0.15707963267948966192e1
 *  
 *  # Quadrant XY diagonals
 *  # For imaginary
 *  ComplexPlane.quadrant(1i, 1i, PREC) #=> 0.78539816339744830962e0
 *  ComplexPlane.quadrant(1i, -1i, PREC) #=> -0.78539816339744830962e0
 *  ComplexPlane.quadrant(-1i, -1i, PREC) #=> -0.23561944901923449288e1
 *  ComplexPlane.quadrant(-1i, 1i, PREC) #=> 0.23561944901923449288e1
 *  
 *  # For same values
 *  ComplexPlane.quadrant(1+1i, 1+1i, PREC) #=> (0.78539816339744830962e0+0i)
 *  ComplexPlane.quadrant(-1+1i, -1+1i, PREC) #=> (-0.23561944901923449288e1+0i)
 *  
 *  # For Different signed the same values
 *  ComplexPlane.quadrant(1-1i, -1+1i, PREC) #=> (-0.78539816339744830962e0+0i)
 *  ComplexPlane.quadrant(-1+1i, 1-1i, PREC) #=> (0.23561944901923449288e1+0i)
 *  ```
 */

static inline VALUE
quadrant_nonfinite(VALUE x, VALUE y, VALUE prec)
{
	const ID div = rb_intern("div");
	const ID mult = rb_intern("mult");
	VALUE w = Qundef, pi = Qundef;
	int x_sgn, y_sgn;
	// Ignore non-regular case
	if (rb_num_nonzero_p(rb_num_imag(x)) ||
	    rb_num_nonzero_p(rb_num_imag(y)))
	{
		goto elsewise;
	}
	// The poles of +y+ axis
	else if ((y_sgn = rb_num_infinite_p(y)) != 0 &&
	         rb_num_finite_p(x))
	{
		VALUE real_x = rb_num_real(x);
		switch (y_sgn) {
		case 1: // 0-Deg
			switch (NUM2INT(rb_num_cmpeql(real_x, INT2FIX(0)))) {
			case -1:
				w = BIG_MINUS_ZERO;
				break;
			case 0:
				if (TYPE(real_x) == T_FLOAT)
					w = rb_BigDecimal_flo(real_x);
				else if (CLASS_OF(real_x) == rb_cBigDecimal)
					w = real_x;
				else
					w = BIG_ZERO;
				break;
			case 1:
				w = BIG_ZERO;
				break;
			}
			break;
		case -1: // 180-Deg
			pi = rb_bigmath_pi(prec);
			switch (NUM2INT(rb_num_cmpeql(real_x, INT2FIX(0)))) {
			case -1:
				w = rb_num_uminus(pi);
				break;
			case 0:
				if (TYPE(real_x) == T_FLOAT)
				{
					w = rb_BigDecimal_flo(real_x);
					w = NUM2INT(rb_BigDecimal_sign(w)) == -1 ?
						rb_num_uminus(pi) : pi;
				}
				else if (CLASS_OF(real_x) == rb_cBigDecimal)
					w = NUM2INT(rb_BigDecimal_sign(real_x)) == -1 ?
						rb_num_uminus(pi) : pi;
				else
					w = pi;
				break;
			case 1:
				w = pi;
				break;
			}
		}
	}
	// The poles of +x+ axis
        else if ((x_sgn = rb_num_infinite_p(x)) != 0 &&
	         rb_num_finite_p(y))
	{
		pi = rb_bigmath_pi(prec);
		switch (x_sgn) {
		case 1: // 90-Deg
			w = rb_funcall(pi, div, 2, INT2FIX(2), prec);
			break;
		case -1: // 270-Deg
			w = rb_funcall(pi, div, 2, INT2FIX(-2), prec);
			break;
		}
	}
	// Diagonals +x+ and +y+
	else if (x_sgn != 0 && y_sgn != 0)
	{
		pi = rb_bigmath_pi(prec);
		if (x_sgn == 1 && y_sgn == 1) // 45-Deg
			w = rb_funcall(pi, div, 2, INT2FIX(4), prec);
		else if (x_sgn == 1 && y_sgn == -1) // 135-Deg
			w = rb_funcall(pi, div, 2, INT2FIX(-4), prec);
		else if (x_sgn == -1 && y_sgn == -1) // 225-Deg
			w = rb_funcall(pi, mult, 2,
				rb_Rational(INT2FIX(-3), INT2FIX(4)), prec);
		else if (x_sgn == -1 && y_sgn == 1) // 315-Deg
                        w = rb_funcall(pi, mult, 2,
                                rb_Rational(INT2FIX(3), INT2FIX(4)), prec);
	}
	else
	{
elsewise:
		if (!rb_num_real_p(x) || !rb_num_real_p(y))
			w = rb_Complex(BIG_NAN, BIG_NAN);
		else
			w = BIG_NAN;
	}
	return w;
}

static inline VALUE
quadrant_argument(VALUE x, VALUE y, VALUE prec)
{
	const ID mult = rb_intern("mult");
	const ID div = rb_intern("div");
	VALUE w = Qundef, pi = Qundef;
	bool nucomp = (!rb_num_real_p(x) || !rb_num_real_p(y)) ? true : false;
	if (rb_num_zero_p(y))
	{

		x = rb_funcall(BIG_ZERO, mult, 2, rb_num_real(x), prec);
		y = rb_funcall(BIG_ZERO, mult, 2, rb_num_real(y), prec);
		switch (NUM2INT(rb_BigDecimal_sign(x))) {
		case 1: // 0-Deg
			switch (NUM2INT(rb_BigDecimal_sign(y))) {
			case 1:
				w = BIG_ZERO;
				break;
			case -1:
				w = BIG_MINUS_ZERO;
				break;
			}
			break;
		case -1: // 180-Deg
			pi = rb_bigmath_pi(prec);
			switch (NUM2INT(rb_BigDecimal_sign(y))) {
			case 1:
				w = pi;
				break;
			case -1:
				w = rb_num_uminus(pi);
				break;
			}
			break;
		}
	}
	else // 90-Deg
	{
		pi = rb_bigmath_pi(prec);
		y = rb_funcall(BIG_ZERO, mult, 2, rb_num_real(y), prec);
		switch (NUM2INT(rb_BigDecimal_sign(y))) {
		case 1:
			w = rb_funcall(pi, div, 2, INT2FIX(2), prec);
			break;
		case -1:
			w = rb_funcall(pi, div, 2, INT2FIX(-2), prec);
			break;
		}
	}
	if (nucomp)
		w = rb_Complex1(w);
	return w;
}

static inline bool
quadrant_diagonal_check(VALUE x, VALUE y)
{
	const ID abs = rb_intern("abs");
	VALUE real_cmp = rb_num_cmpeql(
		rb_funcall(rb_num_real(x), abs, 0),
		rb_funcall(rb_num_real(y), abs, 0));
        VALUE imag_cmp = rb_num_cmpeql(
		rb_funcall(rb_num_imag(x), abs, 0),
		rb_funcall(rb_num_imag(y), abs, 0));
	return (FIX2INT(real_cmp) == 0 && FIX2INT(imag_cmp) == 0);
}

static inline VALUE
quadrant_diagonal(VALUE x, VALUE y, VALUE prec)
{
	const ID div = rb_intern("div");
	const ID mult = rb_intern("mult");
	VALUE w = Qundef, pi = Qundef;
	VALUE x_real = rb_num_real(x), x_imag = rb_num_imag(x),
	      y_real = rb_num_real(y), y_imag = rb_num_imag(y);
	// quadrant(ix, iy), |x| == |y|
	if (rb_num_zero_p(x_real) && rb_num_zero_p(y_real))
	{
		pi = rb_bigmath_pi(prec);
		if (rb_num_positive_p(x_imag)) // 45-Deg
		{
			if (rb_num_positive_p(y_imag))
				w = rb_funcall(pi, div, 2, INT2FIX(4), prec);
			else // if (rb_num_negative_p(y_imag))
				w = rb_funcall(pi, div, 2, INT2FIX(-4), prec);
		}
		else // if rb_num_negative_p(y_imag) // 135-Deg
		{
                        if (rb_num_positive_p(y_imag))
                                w = rb_funcall(pi, mult, 2,
                                	rb_Rational(INT2FIX(3), INT2FIX(4)), prec);
                        else // if (rb_num_negative_p(y_imag))
                                w = rb_funcall(pi, mult, 2,
                                	rb_Rational(INT2FIX(-3), INT2FIX(4)), prec);
		}
		w = rb_Complex1(w);
	}
	// quadrant(x+iy, x+iy)
	else if (NUM2INT(rb_num_cmpeql(x_real, y_real)) == 0 &&
	         NUM2INT(rb_num_cmpeql(x_imag, y_imag)) == 0)
	{
		pi = rb_bigmath_pi(prec);
		if (rb_num_positive_p(x_real))
			w = rb_funcall(pi, div, 2, INT2FIX(4), prec);
		else
			w = rb_funcall(pi, mult, 2,
				rb_Rational(INT2FIX(-3), INT2FIX(4)), prec);
		if (!rb_num_real_p(x) || ! rb_num_real_p(y))
			w = rb_Complex1(w);
	}
	// quadrant(x-iy, -x+iy) or quadrant(-x+iy, x-iy)
        else if (NUM2INT(rb_num_cmpeql(x_real, y_real)) != 0 &&
                 NUM2INT(rb_num_cmpeql(x_imag, y_imag)) != 0)
        {
		pi = rb_bigmath_pi(prec);
 		if (rb_num_positive_p(x_real))
			w = rb_funcall(pi, div, 2, INT2FIX(-4), prec);
		else
			w = rb_funcall(pi, mult, 2,
				rb_Rational(INT2FIX(3), INT2FIX(4)), prec);
		w = rb_Complex1(w);
        }
	return w;
}


static inline VALUE
quadrant_csqrt_iter(RB_BLOCK_CALL_FUNC_ARGLIST(y, c))
{
	return rb_funcall(y, '*', 1, y);
}


static inline VALUE
quadrant_finite(VALUE x, VALUE y, VALUE prec)
{
	const ID sub = rb_intern("sub");
	const ID div = rb_intern("div");
	VALUE w = Qundef, ct = Qundef, t = Qundef, pi = Qundef;
	VALUE x_real = rb_num_real(x), x_imag = rb_num_imag(x),
	      y_real = rb_num_real(y), y_imag = rb_num_imag(y);
	int coordinate = 1;
	// Real solution:
	if (rb_num_zero_p(x_imag) && rb_num_zero_p(y_imag))
	{
		x_real = rb_bigmath_canonicalize(x_real, prec, ARG_REAL, ARG_RAWVALUE);
		y_real = rb_bigmath_canonicalize(y_real, prec, ARG_REAL, ARG_RAWVALUE);
		     if (rb_num_positive_p(x_real) && rb_num_negative_p(y_real))
			coordinate = 4;
		else if (rb_num_negative_p(x_real) && rb_num_negative_p(y_real))
			coordinate = 3;
		else if (rb_num_negative_p(x_real) && rb_num_positive_p(y_real))
			coordinate = 2;
		// BUG-FIX: BigDecimal to Rational drops significant digits
#if 0
		w = rb_Rational(y_real, x_real);
#else
		w = rb_funcall(y_real, div, 2, x_real, prec);
#endif
		if (rb_num_negative_p(w))  w = rb_num_uminus(w); // abs()
#if 0
		t = rb_BigDecimal(w, prec);
#else
		t = w;
#endif
	}
	// Complex solution: -i log( (x+iy) / sqrt(x^2+y^2) )
	else
	{
		const ID sum = rb_intern("sum");
		w = rb_block_call(rb_assoc_new(x, y), sum, 0, NULL,
			quadrant_csqrt_iter, Qnil);
		w = rb_bigmath_csqrt(w, prec);
		ct = rb_funcall1(rb_Complex(x, y), '/', w);
		     if (rb_num_positive_p(rb_num_real(ct)) &&
		         rb_num_negative_p(rb_num_imag(ct)))
			coordinate = 4;
		else if (rb_num_negative_p(rb_num_real(ct)) &&
		         rb_num_negative_p(rb_num_imag(ct)))
			coordinate = 3;
		else if (rb_num_negative_p(rb_num_real(ct)) &&
		         rb_num_positive_p(rb_num_imag(ct)))
			coordinate = 2;
		t = rb_funcall(rb_num_imag(ct), div, 2, rb_num_real(ct), prec);
		if (rb_num_negative_p(t))
			t = rb_num_uminus(t);
	}

	// Calculate tan^{-1}(y/x)
	w = rb_bigmath_atan(t, prec);
	switch (coordinate) {
	case 4:
		w = rb_num_uminus(w);
		break;
	case 3:
		pi = rb_bigmath_pi(prec);
		w = rb_funcall(w, sub, 2, pi, prec);
		break;
	case 2:
		pi = rb_bigmath_pi(prec);
		w = rb_funcall(pi, sub, 2, w, prec);
		break;
	}

	// For Complex solutions
	if (rb_num_nonzero_p(x_imag) || rb_num_nonzero_p(y_imag))
	{
		VALUE abs = rb_bigmath_cabs(ct, prec);
		w = rb_ImaginaryZ(rb_Complex(rb_bigmath_log(abs, prec), w), 
			SIGN_MINUS);
	}

	if (!rb_num_real_p(x) || ! rb_num_real_p(y))
		w = rb_Complex1(w);

	return w;
}

VALUE
rb_bigmath_quadrant(VALUE x, VALUE y, VALUE prec)
{
	VALUE w = Qundef;
	rb_check_precise(prec);
	if (!rb_num_finite_p(x) || !rb_num_finite_p(y))
	{
		w = quadrant_nonfinite(x, y, prec);
	}
	else // if (rb_num_finite_p(x) && rb_num_finite_p(y))
	{
		if (rb_num_zero_p(x) || rb_num_zero_p(y))
		{
			w = quadrant_argument(x, y, prec);
		}
		else
		{
			if (quadrant_diagonal_check(x, y))
			{
				w = quadrant_diagonal(x, y, prec);
			}
			if (w == Qundef)
			{
				w = quadrant_finite(x, y, prec);
			}
		}
	}
	if (w == Qundef)
		rb_raise(rb_eRuntimeError, "no solution");
	return rb_bigmath_round_inline(w, prec);
}


/**
 *  Consider where the value is in quadrant XY and computes the inverse tangent of +y/x+.
 *  
 *  @param x [Numeric] X-axis
 *  @param y [Numeric] Y-axis
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @return [Complex] Complex solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +x+ is not a numeric class.
 *  @since 0.1.0
 */
static VALUE
nucomp_quadrant(VALUE unused_obj, VALUE x, VALUE y, VALUE prec)
{
	return rb_bigmath_quadrant(x, y, prec);
}

/**
 *  Consider where the value is in quadrant XY and computes the inverse tangent of +y/x+.
 *  
 *  @param y [Numeric] Y-axis
 *  @param x [Numeric] X-axis
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @return [Complex] Complex solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +x+ is not a numeric class.
 *  @since 0.1.0
 */
static VALUE
nucomp_math_atan2(VALUE unused_obj, VALUE y, VALUE x, VALUE prec)
{
	return rb_bigmath_quadrant(x, y, prec);
}

VALUE
rb_bigmath_carg(VALUE z, VALUE prec)
{
	return rb_bigmath_quadrant(
		rb_num_real(z), rb_num_imag(z), prec);
}


/**
 *  Return complex argument of +z+.
 *  
 *  @param z [Numeric] Complex variable
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +z+ is not a numeric class.
 *  @since 0.1.0
 */
static VALUE
nucomp_carg(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_bigmath_carg(z, prec);
}


VALUE
rb_bigmath_polar_to(VALUE z, VALUE prec)
{
	return rb_Complex(rb_bigmath_cabs(z, prec), rb_bigmath_carg(z, prec));
}


static VALUE
nucomp_polar_to(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_bigmath_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_bigmath_polar_to(z, prec);
}


VALUE
rb_bigmath_polar_from(VALUE r, VALUE theta, VALUE prec)
{
	const ID mult = rb_intern("mult");
	VALUE sin, cos, t;

	r = rb_bigmath_canonicalize(r, prec, ARG_REAL, ARG_RAWVALUE);
	theta = rb_bigmath_canonicalize(theta, prec, ARG_REAL, ARG_RAWVALUE);

	theta = rb_sincos_to_radian(theta, prec, rb_bigmath_pi(prec), &t);
	if (rb_degree_sparg(t, prec, &sin, &cos) == -1)
		rb_bigmath_sincos(theta, prec, &sin, &cos);
	return rb_Complex(
		rb_funcall(r, mult, 2, cos, prec),
		rb_funcall(r, mult, 2, sin, prec)
	);
}


static VALUE
nucomp_polar_from(VALUE unused_obj, VALUE r, VALUE theta, VALUE prec)
{
	return rb_bigmath_polar_from(r, theta, prec);
}


/**
 *  Document-module:  BigMathR::ComplexPlane
 *  
 *  A module that provides whole of functions related to the complex plane. 
 *  It is used internally.
 *  <br>
 */
void
InitVM_ComplexPlane(void)
{
	rb_define_module_function(rb_mComplexPlane, "l2norm", nucomp_l2norm, -2);
	rb_define_module_function(rb_mComplexPlane, "cabs", nucomp_cabs, 2);
	rb_define_module_function(rb_mComplexPlane, "quadrant", nucomp_quadrant, 3);
	rb_define_module_function(rb_mComplexPlane, "carg", nucomp_carg, 2);
	rb_define_module_function(rb_mComplexPlane, "polar_to", nucomp_polar_to, 2);
	rb_define_module_function(rb_mComplexPlane, "polar_from", nucomp_polar_from, 3);

	rb_define_module_function(rb_mBigMathR, "hypot", nucomp_math_hypot, 3);
	rb_define_module_function(rb_mBigMathR, "atan2", nucomp_math_atan2, 3);
}
