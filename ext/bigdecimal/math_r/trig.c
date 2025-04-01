/*******************************************************************************
	trig.c -- Trigonometric Function

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"

/**
 * It is equivalent to the following Ruby code:
 *  ```Ruby
 *  def sincos_to_radian(x, prec)
 *    twopi = BigMath.PI(prec) * BigDecimal(2)
 *    if x < -twopi or twopi < x
 *      x = -x if neg = x < 0
 *      if x > 30
 *        x %= twopi
 *      else
 *        x -= twopi while x > twopi
 *      end
 *      x = -x if neg
 *    else
 *      x = case x
 *      when Integer
 *        BigDecimal(x)
 *      when Float
 *        BigDecimal(x, Float::DIG)
 *      when Rational
 *        BigDecimal(x, prec)
 *      when Complex
 *        raise TypeError, "no solution for Complex"
 *      else
 *        x
 *      end
 *    end
 *    if x < (-twopi/2)
 *      x + twopi
 *    elsif (twopi/2) < x
 *      x - twopi
 *    else
 *      x
 *    end
 *  end
 *  ```
 */
VALUE
rb_sincos_to_radian(VALUE x, VALUE prec, VALUE pi, VALUE *t)
{
	const ID mult = rb_intern("mult");
	VALUE twopi = rb_funcall1(pi, '*', INT2FIX(2));
	bool neg = false;
	if (NUM2INT(rb_num_cmpeql(x, rb_num_uminus(twopi))) == -1 ||
	    NUM2INT(rb_num_cmpeql(twopi, x)) == -1)
	{
		neg = rb_num_negative_p(x);
		if (neg)
			x = rb_num_uminus(x);
		if (rb_num_cmpeql(x, INT2FIX(30)) == 1)
			x = rb_funcall1(x, '%', twopi);
		else
			do x = rb_funcall1(x, '-', twopi);
				while (INT2FIX(rb_num_cmpeql(x, twopi)) == 1);
		if (neg)
			x = rb_num_uminus(x);
	}
	else
	{
		x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	}
	if (t != NULL)
	{
		*t = rb_num_round(
			rb_funcall1(x, '/', twopi), prec);
		if (rb_num_negative_p(*t))
			rb_funcall1(x, '+', INT2FIX(1));
		*t = rb_funcall(*t, mult, 2, INT2FIX(360), prec);
	}
	if (NUM2INT(rb_num_cmpeql(x, rb_num_uminus(pi))) == -1)
		x = rb_funcall1(x, '+', twopi);
	else if   (NUM2INT(rb_num_cmpeql(pi, x)) == -1)
		x = rb_funcall1(x, '-', twopi);
	return x;
}


/**
 *  Degree  | Rational | $P(x, y) = (\cos\theta, \sin\theta)$
 *  360-deg |      0/1 | $(1, 0)$
 *   30-deg |      1/6 | $(\frac{\sqrt{3}}{2}, \frac{1}{2})$
 *   45-deg |      1/4 | $(\frac{\sqrt{2}}{2}, \frac{\sqrt{2}}{2})$
 *   60-deg |      1/3 | $(\frac{1}{2}, \frac{\sqrt{3}}{2})$
 *   90-deg |      1/2 | $(0, 1)$
 *  120-deg |      2/3 | $(-\frac{1}{2}, \frac{\sqrt{3}}{2})$
 *  135-deg |      3/4 | $(-\frac{\sqrt{2}}{2}, \frac{\sqrt{2}}{2})$
 *  150-deg |      5/6 | $(-\frac{\sqrt{3}}{2}, \frac{1}{2})$
 *  180-deg |      1/1 | $(-1, 0)$
 *  210-deg |      7/6 | $(-\frac{\sqrt{3}}{2}, -\frac{1}{2})$
 *  225-deg |      5/4 | $(-\frac{\sqrt{2}}{2}, -\frac{\sqrt{2}}{2})$
 *  240-deg |      4/3 | $(-\frac{1}{2}, -\frac{\sqrt{3}}{2})$
 *  270-deg |      3/2 | $(0, -1)$
 *  300-deg |      5/3 | $(\frac{1}{2}, -\frac{\sqrt{3}}{2})$
 *  315-deg |      7/4 | $(\frac{\sqrt{2}}{2}, -\frac{\sqrt{2}}{2})$
 *  330-deg |     11/6 | $(\frac{\sqrt{3}}{2}, -\frac{1}{2})$
 *
 *  ```Ruby
 *  def sparg_list(prec)
 *    funcs = [:sin, :cos, :tan, :csc, :sec, :cot]
 *    degrees = [
 *      0/1r, 1/6r, 1/4r, 1/3r, 1/2r, 2/3r, 3/4r, 5/6r,
 *        1r, 7/6r, 5/4r, 4/3r, 3/2r, 5/3r, 7/4r, 11/6r
 *    ]
 *    degree_num = [
 *      360,  30,  45,  60,  90, 120, 135, 150,
 *      180, 210, 225, 240, 270, 300, 315, 330
 *    ]
 *    pi = BigMath.PI(prec)
 *  
 *    puts (["Degree"] + funcs).map{|func| (" " + func.to_s).ljust(prec+5, " ")}.join("  ")
 *  
 *    degree_num.zip(degrees).each do |deg, rat|
 *      list = [deg]
 *      funcs.each do |func|
 *        meth = BigMathR::Trigonometric.method(func)
 *        y = meth.call(rat * pi, prec)
 *        list << y
 *      end
 *      puts list.map{|x| ((x = x.to_s)[0] == '-' ? x : " " + x.to_s).ljust(prec+5, " ")}.join("  ")
 *    end
 *  end
 *  ```
 *  
 *  ```
 *  $ sparg_list(8)
 *   Degree         sin            cos            tan            csc            sec            cot         
 *   360            0.0            0.1e1          0.0            Infinity       0.1e1          Infinity    
 *   30             0.5e0          0.8660254e0    0.57735027e0   0.2e1          0.11547005e1   0.17320508e1
 *   45             0.70710678e0   0.70710678e0   0.1e1          0.14142136e1   0.14142136e1   0.1e1       
 *   60             0.8660254e0    0.5e0          0.17320508e1   0.11547005e1   0.2e1          0.57735027e0
 *   90             0.1e1          0.0            Infinity       0.1e1          Infinity       0.0         
 *   120            0.8660254e0   -0.5e0         -0.17320508e1   0.11547005e1  -0.2e1         -0.57735027e0
 *   135            0.70710678e0  -0.70710678e0  -0.1e1          0.14142136e1  -0.14142136e1  -0.1e1       
 *   150            0.5e0         -0.8660254e0   -0.57735027e0   0.2e1         -0.11547005e1  -0.17320508e1
 *   180            0.0           -0.1e1         -0.0            Infinity      -0.1e1         -Infinity    
 *   210           -0.5e0         -0.8660254e0    0.57735027e0  -0.2e1         -0.11547005e1   0.17320508e1
 *   225           -0.70710678e0  -0.70710678e0   0.1e1         -0.14142136e1  -0.14142136e1   0.1e1       
 *   240           -0.8660254e0   -0.5e0          0.17320508e1  -0.11547005e1  -0.2e1          0.57735027e0
 *   270           -0.1e1          0.0           -Infinity      -0.1e1          Infinity      -0.0         
 *   300           -0.8660254e0    0.5e0         -0.17320508e1  -0.11547005e1   0.2e1         -0.57735027e0
 *   315           -0.70710678e0   0.70710678e0  -0.1e1         -0.14142136e1   0.14142136e1  -0.1e1       
 *   330           -0.5e0          0.8660254e0   -0.57735027e0  -0.2e1          0.11547005e1  -0.17320508e1
 *  ```
 * --------------------------------- SYNOPSIS ---------------------------------
 */

int
rb_degree_sparg(VALUE t, VALUE prec, VALUE *sin, VALUE *cos)
{
	const ID div = rb_intern("div");
#define angle_equal_p(d) \
	rb_num_equal_p(t, INT2FIX(d))
#define HALF \
	rb_funcall(BIG_ONE, div, 2, INT2FIX(2), prec)
#define HALF_M \
	rb_funcall(BIG_ONE, div, 2, INT2FIX(-2), prec)
#define SQRT2_2 \
	rb_funcall(rb_bigmath_const_sqrt2(prec), div, 2, INT2FIX(2), prec)
#define SQRT2_2_M \
	rb_funcall(rb_bigmath_const_sqrt2(prec), div, 2, INT2FIX(-2), prec)
#define SQRT3_2 \
	rb_funcall(rb_bigmath_const_sqrt3(prec), div, 2, INT2FIX(2), prec)
#define SQRT3_2_M \
	rb_funcall(rb_bigmath_const_sqrt3(prec), div, 2, INT2FIX(-2), prec)

	if (angle_equal_p(0))
	{
		if (cos != NULL)  *cos = BIG_ONE;
		if (sin != NULL)  *sin = BIG_ZERO;
		return 1;
	}
	else if (angle_equal_p(30))
	{
		if (cos != NULL)  *cos = SQRT3_2;
		if (sin != NULL)  *sin = HALF;
		return 1;
	}
	else if (angle_equal_p(45))
	{
		if (cos != NULL)  *cos = SQRT2_2;
		if (sin != NULL)  *sin = SQRT2_2;
		return 1;
	}
	else if (angle_equal_p(60))
	{
		if (cos != NULL)  *cos = HALF;
		if (sin != NULL)  *sin = SQRT3_2;

		return 1;
	}
	else if (angle_equal_p(90))
	{
		if (cos != NULL)  *cos = BIG_ZERO;
		if (sin != NULL)  *sin = BIG_ONE;
		return 1;
	}
	else if (angle_equal_p(120))
	{
		if (cos != NULL)  *cos = HALF_M;
		if (sin != NULL)  *sin = SQRT3_2;
		return 1;
	}
	else if (angle_equal_p(135))
	{
		if (cos != NULL)  *cos = SQRT2_2_M;
		if (sin != NULL)  *sin = SQRT2_2; 
		return 1;
	}
	else if (angle_equal_p(150))
	{
		if (cos != NULL)  *cos = SQRT3_2_M;
		if (sin != NULL)  *sin = HALF;
		return 1;
	}
	else if (angle_equal_p(180))
	{
		if (cos != NULL)  *cos = BIG_MINUS_ONE;
		if (sin != NULL)  *sin = BIG_ZERO;
		return 1;
	}
	else if (angle_equal_p(210))
	{
		if (cos != NULL)  *cos = SQRT3_2_M;
		if (sin != NULL)  *sin = HALF_M;
		return 1;
	}
	else if (angle_equal_p(225))
	{
		if (cos != NULL)  *cos = SQRT2_2_M;
		if (sin != NULL)  *sin = SQRT2_2_M;
		return 1;
	}
	else if (angle_equal_p(240))
	{
		if (cos != NULL)  *cos = HALF_M;
		if (sin != NULL)  *sin = SQRT3_2_M;
		return 1;
	}
	else if (angle_equal_p(270))
	{
		if (cos != NULL)  *cos = BIG_ZERO;
		if (sin != NULL)  *sin = BIG_MINUS_ONE;
		return 1;
	}
	else if (angle_equal_p(300))
	{
		if (cos != NULL)  *cos = HALF;
		if (sin != NULL)  *sin = SQRT3_2_M;
		return 1;
	}
	else if (angle_equal_p(315))
	{
		if (cos != NULL)  *cos = SQRT2_2;
		if (sin != NULL)  *sin = SQRT2_2_M;
		return 1;
	}
	else if (angle_equal_p(330))
	{
		if (cos != NULL)  *cos = SQRT3_2;
		if (sin != NULL)  *sin = HALF_M;
		return 1;
	}
#undef angle_equal_p
#undef HALF
#undef HALF_M
#undef SQRT2_2
#undef SQRT2_2_M
#undef SQRT3_2
#undef SQRT3_2_M
	else
	{
		return -1;
	}
}

static VALUE
sincos_fig(VALUE deg, VALUE f)
{
	const ID exponent = rb_intern("exponent");
	deg = rb_funcall1(deg, '-', rb_funcall(f, exponent, 0));
	return deg;
}

/**
 *  It is equivalent to the following Ruby code:
 *  ```Ruby
 *  def sincos(func, x, prec)
 *    raise TypeError, "precision must be an Integer" unless prec.class == Integer
 *    raise RangeError, "zero or negative precision" if prec <= 0
 *    calc_sin = false; calc_cos = false
 *    case func
 *    when :sin, :csc
 *      calc_sin = true
 *    when :cos, :sec
 *      calc_cos = true
 *    when :sincos, :tan, :cot
 *      calc_sin = true; calc_cos = true
 *    else
 *      raise ArgumentError, "unrecognized function name: #{func}"
 *    end
 *  
 *    return BigDecimal::NAN if x.infinite? or x != x
 *    n = prec + BigDecimal.double_fig
 *    x = sincos_to_radian(x, prec)
 *    i = 0
 *    f = BigDecimal(1)
 *    w = BigDecimal(1)
 *    a = BigDecimal(1)
 *    sin = BigDecimal(0)
 *    cos = BigDecimal(0)
 *    while a.nonzero? && (m = (n - f.exponent).abs) > 0
 *      m = BigDecimal.double_fig if m < BigDecimal.double_fig
 *      a = w.div(f, m)
 *      case i % 4
 *      when 0
 *        cos += a if calc_cos
 *      when 1
 *        sin += a if calc_sin
 *      when 2
 *        cos -= a if calc_cos
 *      when 3
 *        sin -= a if calc_sin
 *      end
 *      w = w.mult(x, n)
 *      i = i.succ
 *      f = f.mult(i, n)
 *    end
 *  
 *    case func
 *    when :sin
 *      sin.round(prec)
 *    when :cos
 *      cos.round(prec)
 *    when :sincos
 *      [sin.round(prec), cos.round(prec)]
 *    when :tan
 *      sin.round(prec).div(cos.round(prec), prec)
 *    when :csc
 *      BigDecimal(1).div(sin, prec)
 *    when :sec
 *      BigDecimal(1).div(cos, prec)
 *    when :cot
 *      cos.round(prec).div(sin.round(prec), prec)
 *    end
 *  end
 *  ```
 * 
 * In this Ruby code, you can create the value of the entire trigonometric 
 * function. In C code, you need to be more aware of function procedures.
 */

void
rb_bigmath_sincos(VALUE x, VALUE prec, VALUE *sin, VALUE *cos)
{
	const ID double_fig = rb_intern("double_fig");
	const ID mult = rb_intern("mult");
	const ID div = rb_intern("div");
	VALUE deg, m, dbl_fig;
	VALUE f, w, a;
	long n = 0;

	if (!rb_num_finite_p(x))
	{
		if (sin != NULL)  *sin = BIG_NAN;
		if (cos != NULL)  *cos = BIG_NAN;
		return;
	}
	dbl_fig = rb_funcall(rb_cBigDecimal, double_fig, 0);
	deg = rb_funcall1(prec, '+', dbl_fig);
	f = BIG_ONE;
	w = BIG_ONE;
	a = BIG_ONE;
	if (sin != NULL)  *sin = BIG_ZERO;
	if (cos != NULL)  *cos = BIG_ZERO;
	while (rb_num_nonzero_p(a) &&
	       NUM2INT(rb_num_cmpeql(m = sincos_fig(deg, f), INT2FIX(0))) == 1)
	{
		if (NUM2INT(rb_num_cmpeql(m, dbl_fig)) == -1)
			m = dbl_fig;
		a = rb_funcall(w, div, 2, f, m);
		switch (n % 4) {
		case 0:
			if (cos != NULL)  *cos = rb_funcall1(*cos, '+', a);
			break;
		case 1:
                        if (sin != NULL)  *sin = rb_funcall1(*sin, '+', a);
 			break;
		case 2:
                        if (cos != NULL)  *cos = rb_funcall1(*cos, '-', a);
 			break;
		case 3:
                        if (sin != NULL)  *sin = rb_funcall1(*sin, '-', a);
 			break;
		}
		w = rb_funcall(w, mult, 2, x, deg);
		f = rb_funcall(f, mult, 2, LONG2NUM(++n), deg);
	}
	RB_GC_GUARD(f);
	RB_GC_GUARD(w);
	RB_GC_GUARD(a);
	if (sin != NULL)  RB_GC_GUARD(*sin);
	if (cos != NULL)  RB_GC_GUARD(*cos);
}


/**
 * Computes at once sine and cosine of +x+.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Array] Real solutions [sin(x), cos(x)]
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::Trigonometric.sincos(1, 20)
 *  #=> [0.84147098480789650665e0, 0.5403023058681397174e0]
 * @since 0.1.0
 */
static VALUE
__impl_trig_sincos(VALUE unused_obj, VALUE x, VALUE prec)
{
	VALUE sin, cos, pi, t;
	rb_check_precise(prec);
	if (!rb_num_finite_p(x))
		return rb_assoc_new(BIG_NAN, BIG_NAN);
	pi = rb_bigmath_const_pi(prec);
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	x = rb_sincos_to_radian(x, prec, pi, &t);
	if (rb_degree_sparg(t, prec, &sin, &cos) == -1)
		rb_bigmath_sincos(x, prec, &sin, &cos);
	sin = rb_num_round(sin, prec);
	cos = rb_num_round(cos, prec);
	return rb_assoc_new(sin, cos);
}


static VALUE
rb_bigmath_sin(VALUE x, VALUE prec)
{
	VALUE sin, pi, t;
	rb_check_precise(prec);
	if (!rb_num_finite_p(x))
		return BIG_NAN;
	pi = rb_bigmath_const_pi(prec);
	x = rb_sincos_to_radian(x, prec, pi, &t);
	if (rb_degree_sparg(t, prec, &sin, NULL) == -1)
		rb_bigmath_sincos(x, prec, &sin, NULL);
	sin = rb_num_round(sin, prec);
	return sin;
}


/**
 * Computes sine of +x+. 
 * <br>
 * +x+ gives in radian.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::Trigonometric.sin(1, 20)
 *  #=> 0.84147098480789650665e0
 * @since 0.1.0
 */
static VALUE
__impl_trig_sin(VALUE unused_obj, VALUE x, VALUE prec)
{
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_bigmath_sin(x, prec);
}


static VALUE
rb_bigmath_cos(VALUE x, VALUE prec)
{
	VALUE cos, pi, t;
	rb_check_precise(prec);
	if (!rb_num_finite_p(x))
		return BIG_NAN;
	pi = rb_bigmath_const_pi(prec);
	x = rb_sincos_to_radian(x, prec, pi, &t);
	if (rb_degree_sparg(t, prec, NULL, &cos) == -1)
		rb_bigmath_sincos(x, prec, NULL, &cos);
	cos = rb_num_round(cos, prec);
	return cos;
}


/**
 * Computes cosine of +x+.
 * <br>
 * +x+ gives in radian.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::Trigonometric.cos(1, 20)
 *  #=> 0.5403023058681397174e0
 * @since 0.1.0
 */
static VALUE
__impl_trig_cos(VALUE unused_obj, VALUE x, VALUE prec)
{
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_bigmath_cos(x, prec);
}


static VALUE
rb_bigmath_tan(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE sin, cos, pi, t;
	rb_check_precise(prec);
	if (!rb_num_finite_p(x))
		return BIG_NAN;
	pi = rb_bigmath_const_pi(prec);
	x = rb_sincos_to_radian(x, prec, pi, &t);
	if (rb_degree_sparg(t, prec, &sin, &cos) == -1)
		rb_bigmath_sincos(x, prec, &sin, &cos);
	sin = rb_num_round(sin, prec);
	cos = rb_num_round(cos, prec);
	return rb_funcall(sin, div, 2, cos, prec);
}


/**
 * Computes tangent of +x+.
 * <br>
 * +x+ gives in radian.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::Trigonometric.tan(1, 20)
 *  #=> 0.15574077246549022305e1
 * @since 0.1.0
 */
static VALUE
__impl_trig_tan(VALUE unused_obj, VALUE x, VALUE prec)
{
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_bigmath_tan(x, prec);
}


static VALUE
rb_bigmath_csc(VALUE x, VALUE prec)
{
	VALUE sin, pi, t;
	rb_check_precise(prec);
	if (!rb_num_finite_p(x))
		return BIG_NAN;
	pi = rb_bigmath_const_pi(prec);
	x = rb_sincos_to_radian(x, prec, pi, &t);
	if (rb_degree_sparg(t, prec, &sin, NULL) == -1)
		rb_bigmath_sincos(x, prec, &sin, NULL);
	sin = rb_num_round(sin, prec);
	return rb_num_canonicalize(sin, prec, ARG_REAL, ARG_RECIPROCAL);
}


/**
 * Computes cosecant of +x+.
 * <br>
 * +x+ gives in radian.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::Trigonometric.csc(1, 20)
 *  #=> 0.11883951057781212163e1
 * @since 0.1.0
 */
static VALUE
__impl_trig_csc(VALUE unused_obj, VALUE x, VALUE prec)
{
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_bigmath_csc(x, prec);
}


static VALUE
rb_bigmath_sec(VALUE x, VALUE prec)
{
	VALUE cos, pi, t;
	rb_check_precise(prec);
	if (!rb_num_finite_p(x))
		return BIG_NAN;
	pi = rb_bigmath_const_pi(prec);
	x = rb_sincos_to_radian(x, prec, pi, &t);
	if (rb_degree_sparg(t, prec, NULL, &cos) == -1)
		rb_bigmath_sincos(x, prec, NULL, &cos);
	cos = rb_num_round(cos, prec);
	return rb_num_canonicalize(cos, prec, ARG_REAL, ARG_RECIPROCAL);
}


/**
 * Computes secant of +x+.
 * <br>
 * +x+ gives in radian.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::Trigonometric.sec(1, 20)
 *  #=> 0.18508157176809256179e1
 * @since 0.1.0
 */
static VALUE
__impl_trig_sec(VALUE unused_obj, VALUE x, VALUE prec)
{
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_bigmath_sec(x, prec);
}


static VALUE
rb_bigmath_cot(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE sin, cos, pi, t;
	rb_check_precise(prec);
	if (!rb_num_finite_p(x))
		return BIG_NAN;
	pi = rb_bigmath_const_pi(prec);
	x = rb_sincos_to_radian(x, prec, pi, &t);
	if (rb_degree_sparg(t, prec, &sin, &cos) == -1)
		rb_bigmath_sincos(x, prec, &sin, &cos);
	sin = rb_num_round(sin, prec);
	cos = rb_num_round(cos, prec);
	return rb_funcall(cos, div, 2, sin, prec);
}


/**
 * Computes cotangent of +x+.
 * <br>
 * +x+ gives in radian.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::Trigonometric.cot(1, 20)
 *  #=> 0.64209261593433070301e0
 * @since 0.1.0
 */
static VALUE
__impl_trig_cot(VALUE unused_obj, VALUE x, VALUE prec)
{
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_bigmath_cot(x, prec);
}

/**
 *  Document-module: BigMathR::Trigonometric
 *  
 *  A module that provide the trigonometric functions.
 *  It is used internally.
 *  <br>
 *  All module functions are implemented by +:sincos+.
 *  <br>
 *  == Synopsis
 *  The function names defined are the same as those in the C/C++ standard.
 *  <br>
 *  - Sine:                +:sin+ <br>
 *  - Cosine:              +:cos+ <br>
 *  - Tangent:             +:tan+ <br>
 *  Follow, those reciprocals of not defined in C/C++ standard.
 *  <br>
 *  - Cosecant:            +:csc+ <br>
 *  - Secant:              +:sec+ <br>
 *  - Cotangent:           +:cot+ <br>
 *  The following are GNU extensions:
 *  <br>
 *  - sincos():            +:sincos+ <br>
 *  Reference::
 *  Kiso kara hatten made Sankaku kansuu (Japanese) - Michimasa Kobayashi (Beret Shuppan)
 */
void
InitVM_Trigonometric(void)
{
	rb_define_module_function(rb_mTrigonometric, "sincos", __impl_trig_sincos, 2);
	rb_define_module_function(rb_mTrigonometric, "sin", __impl_trig_sin, 2);
	rb_define_module_function(rb_mTrigonometric, "cos", __impl_trig_cos, 2);
	rb_define_module_function(rb_mTrigonometric, "tan", __impl_trig_tan, 2);
	rb_define_module_function(rb_mTrigonometric, "csc", __impl_trig_csc, 2);
	rb_define_module_function(rb_mTrigonometric, "sec", __impl_trig_sec, 2);
	rb_define_module_function(rb_mTrigonometric, "cot", __impl_trig_cot, 2);
}
