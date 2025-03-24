/*******************************************************************************
	constant.c -- Mathematical constants

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "internal/solver/bigmath_r.h"

#define DEF_PREC 1000
#define BIGMATH_PI     "$M_PI"
#define BIGMATH_E      "$M_E"
#define BIGMATH_LOG2   "$M_LOG2"
#define BIGMATH_LOG10  "$M_LOG10"
#define BIGMATH_SQRT2  "$M_SQRT2"
#define BIGMATH_SQRT3  "$M_SQRT3"

static VALUE
init_prec(VALUE prec)
{
	const ID double_fig = rb_intern("double_fig");
	VALUE fig, retval = Qnil;

	rb_check_precise(prec);

	fig = rb_funcall(rb_cBigDecimal, double_fig, 0);

	switch (NUM2INT(rb_dbl_cmp(NUM2DBL(prec), NUM2DBL(fig)))) {
	case -1:
		retval = fig;
		break;
	case 0:
	case 1:
		retval = prec;
	}

	return retval;
}

static inline bool
check_eps(VALUE x, VALUE prec)
{
	const ID exponent = rb_intern("exponent");
	return (rb_num_negative_p(
		rb_funcall(
			rb_funcall(x, exponent, 0),
			'+', 1, 
			prec
	)));
}


/**
 *  Is the implementation by the formula of Machin the fastest?
 *  ```Ruby
 *  # frozen_string_literal: true
 *  
 *  require 'bigdecimal/math'
 *  
 *  def PI_euler(prec)
 *    raise ArgumentError, "Zero or negative precision for PI" if prec <= 0
 *    one = BigDecimal(1)
 *    two = BigDecimal(2)
 *    s = BigDecimal(0)
 *    t = one
 *    t1 = BigDecimal(0)
 *    t2 = one
 *    n = prec + BigDecimal.double_fig
 *    while t.nonzero? && ((m = n - (s.exponent - t.exponent).abs) > 0)
 *      m = BigDecimal.double_fig if m < BigDecimal.double_fig
 *      s = s + t
 *      t1 = t1 + one;  t = t.mult(t1, m)
 *      t2 = t2 + two;  t = t.div(t2, m)
 *    end
 *    two.mult(s, prec)
 *  end
 *  
 *  def PI_machin(prec)
 *    raise ArgumentError, "Zero or negative precision for PI" if prec <= 0
 *    one = BigDecimal(1)
 *    two = BigDecimal(2)
 *    m25 = BigDecimal('-0.04')
 *    m57121 = BigDecimal('-57121')
 *    m = prec + BigDecimal.double_fig
 *    pi = BigDecimal(0)
 *    k = one
 *    t = BigDecimal(16/5r, m)
 *    loop do
 *      pi = pi + t.div(k, m)
 *      t = t * m25
 *      k = k+two
 *      break if (t.exponent + m) < 0
 *    end
 *    k = one
 *    t = BigDecimal(4/239r, m)
 *    loop do
 *      pi = pi - t.div(k, m)
 *      t = t.div(m57121, m)
 *      k = k+two
 *      break if (t.exponent + m) < 0
 *    end
 *    pi.round(prec)
 *  end
 *  
 *  def main
 *    require 'benchmark'
 *    prec = 20
 *    n = 10000
 *    Benchmark.bm(22) do |bmx|
 *      bmx.report("Euler's PI (Ruby code)") { for i in 1..n do; PI_euler(prec) end }
 *      bmx.report("Machin's PI (Ruby code)") { for i in 1..n do; PI_machin(prec) end }
 *    end
 *  end
 *  
 *  main
 *  ```
 * 
 * The result of the execution is as follows:
 * (Environment: AMD Ryzen™ 7 5800X × 16)
 * 
 *  ```
 *  $ ruby pi.rb
 *                               user     system      total        real
 *  Euler's PI (Ruby code)   1.289779   0.003097   1.292876 (  1.292945)
 *  Machin's PI (Ruby code)  0.348689   0.001007   0.349696 (  0.349779)
 *  ```
 *
 * --------------------------------- SYNOPSIS ---------------------------------
 */
static VALUE
calc_pi(VALUE prec)
{
#if 0
        const ID _PI = rb_intern("PI");
	return rb_funcall(rb_mBigMath, _PI, 1, prec);
#else
	const ID div = rb_intern("div");
	VALUE m, n, one, two, m25, m57121, pi, k, t, d;
	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);
	one = BIG_ONE;
	two = rb_BigDecimal1(INT2FIX(2));
	m25 = rb_BigDecimal1(rb_str_new_cstr("-0.04"));
	m57121 = rb_BigDecimal1(rb_str_new_cstr("-57121"));
	pi = BIG_ZERO;
	k = BIG_ONE;
	t = rb_BigDecimal(rb_Rational(INT2FIX(16), INT2FIX(5)), n);
	d = one;
	while (rb_numdiff_condition_p(pi, d, n, &m))
	{
		rb_numdiff_keep_fig(&m);
		d = rb_funcall(t, div, 2, k, m);
		pi = rb_funcall1(pi, '+', d);
		t = rb_funcall1(t, '*', m25);
		k = rb_funcall1(k, '+', two);
	}
	k = BIG_ONE;
	t = rb_BigDecimal(rb_Rational(INT2FIX(4), INT2FIX(239)), n);
	d = one;
	while (rb_numdiff_condition_p(pi, d, n, &m))
	{
		rb_numdiff_keep_fig(&m);
		d = rb_funcall(t, div, 2, k, m);
		pi = rb_funcall1(pi, '-', d);
		t = rb_funcall(t, div, 2, m57121, n);
		k = rb_funcall1(k, '+', two);
	}
	RB_GC_GUARD(one);
	RB_GC_GUARD(two);
	RB_GC_GUARD(m25);
	RB_GC_GUARD(m57121);
	RB_GC_GUARD(pi);
	RB_GC_GUARD(k);
	RB_GC_GUARD(t);
	RB_GC_GUARD(d);
	return rb_bigmath_round_inline(pi, prec);
#endif
}
/**
 * Compare implementations:
 * 
 *  ```Ruby
 *  def main
 *    require 'benchmark'
 *    prec = 2000
 *    Benchmark.bm(22) do |bmx|
 *      bmx.report("PI (C code)") { BigMathR.PI(prec) }
 *      bmx.report("PI (Ruby code)") { BigMath.PI(prec) }
 *    end
 *  end
 *  
 *  main
 *  ```
 * 
 * Result as follow:
 *  ```
 *                               user     system      total        real
 *  PI (C code)              0.061413   0.006079   0.067492 (  0.067293)
 *  PI (Ruby code)           0.034272   0.003993   0.038265 (  0.038176)
 *  ```
 * Ruby code is faster.
 */


static VALUE
math_pi_set_inline(VALUE prec)
{
	return rb_gv_set(BIGMATH_PI, calc_pi(prec));
}

VALUE
rb_bigmath_pi(VALUE prec)
{
	static int def_prec = DEF_PREC;
	VALUE m_pi = rb_gv_get(BIGMATH_PI);

	prec = init_prec(prec);
	if (def_prec < NUM2INT(prec))
	{
		def_prec = NUM2LONG(prec);
		m_pi = math_pi_set_inline(INT2FIX(def_prec));
	}

	if (NIL_P(m_pi))
		m_pi = math_pi_set_inline(INT2FIX(def_prec));

        return rb_bigmath_round_inline(m_pi, prec);
}


/**
 * The constant pi.
 * @example
 *  BigMathR.PI(20) #=> 0.314159265358979323846e1
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @since 0.1.0
 */
static VALUE
const_math_pi(VALUE unused_obj, VALUE prec)
{
	return rb_bigmath_pi(prec);
}


/**
 * 
 *  ```Ruby
 *  def E(prec)
 *    m = prec + BigDecimal.double_fig
 *    a = BigDecimal(1)
 *    e = BigDecimal(0)
 *    n = 0
 *    loop do
 *      e = e.add(a, m); n = n.succ; a = a.div(n, m)
 *      break if (a.exponent + m) < 0
 *    end
 *    e.round(prec)
 *  end
 *  ```
 */
static VALUE
calc_e(VALUE prec)
{
#if 0
	const ID _E = rb_intern("E");
	return rb_funcall(rb_mBigMath, _E, 1, prec);
#else
	const ID div = rb_intern("div");
	VALUE n = rb_numdiff_make_n(prec);
	VALUE a = BIG_ONE;
	VALUE e = BIG_ZERO;
	long k = 0; // TODO: should be break when number is exceeded to LONG_MAX?
	while (!check_eps(a, n))
	{
		e = rb_funcall1(e, '+', a);
		a = rb_funcall(a, div, 2, LONG2NUM(++k), n);
	}
	RB_GC_GUARD(a);
	RB_GC_GUARD(e);
        return rb_bigmath_round_inline(e, prec);
#endif
}

static VALUE
math_e_set_inline(VALUE prec)
{
	return rb_gv_set(BIGMATH_E, calc_e(prec));
}

VALUE
rb_bigmath_e(VALUE prec)
{
	static int def_prec = DEF_PREC;
	VALUE m_e = rb_gv_get(BIGMATH_E);

	prec = init_prec(prec);
	if (def_prec < NUM2INT(prec))
	{
		def_prec = NUM2LONG(prec);
		m_e = math_e_set_inline(INT2FIX(def_prec));
	}

	if (NIL_P(m_e))
		m_e = math_e_set_inline(INT2FIX(def_prec));

        return rb_bigmath_round_inline(m_e, prec);
}


/**
 * The constant e.
 * @example
 *  BigMathR.E(20) #=> 0.27182818284590452354e1
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @since 0.1.0
 */
static VALUE
const_math_e(VALUE unused_obj, VALUE prec)
{
	return rb_bigmath_e(prec);
}


/**
 *  The following is the implementation in Ruby code:
 *  ```Ruby
 *  def LOG2(prec)
 *    a = 1
 *    r = BigDecimal(1)
 *    s = 0
 *    loop do
 *      t = r.div(a, prec)
 *      s += t
 *      break if (t.exponent + prec) < 0
 *      a += 2
 *      r = r.div(9, prec)
 *    end
 *    s.mult(2/3r, prec)
 *  end
 *  ```
 */

static VALUE
calc_log2(VALUE prec)
{
	const ID mult = rb_intern("mult");
	const ID div = rb_intern("div");
	VALUE two = rb_BigDecimal1(INT2FIX(2)),
	      nine = rb_BigDecimal1(INT2FIX(9)),
	      a = BIG_ONE,
	      r = BIG_ONE,
	      s = BIG_ZERO,
	      d = BIG_ONE,
	      n = rb_numdiff_make_n(prec);
	while (!check_eps(d, n))
	{
		d = rb_funcall(r, div, 2, a, n);
		s = rb_funcall1(s, '+', d);
		a = rb_funcall1(a, '+', two);
		r = rb_funcall(r, div, 2, nine, n);
	}
	s = rb_funcall(s, mult, 2,
		rb_Rational(INT2FIX(2), INT2FIX(3)), prec);
	RB_GC_GUARD(two);
	RB_GC_GUARD(nine);
	RB_GC_GUARD(d);
	RB_GC_GUARD(a);
	RB_GC_GUARD(r);
	RB_GC_GUARD(s);
	return s;
}

static VALUE
math_log2_set_inline(VALUE prec)
{
	return rb_gv_set(BIGMATH_LOG2, calc_log2(prec));
}

VALUE
rb_bigmath_const_log2(VALUE prec)
{
	static int def_prec = DEF_PREC;
	VALUE m_log2 = rb_gv_get(BIGMATH_LOG2);
	prec = init_prec(prec);
	if (def_prec < NUM2INT(prec))
	{
		def_prec = NUM2LONG(prec);
		m_log2 = math_log2_set_inline(INT2FIX(def_prec));
	}

	if (NIL_P(m_log2))
		m_log2 = math_log2_set_inline(INT2FIX(def_prec));

        return rb_bigmath_round_inline(m_log2, prec);
}


/**
 * The natural logarithm of 2.
 * @example
 *  BigMathR.LOG2(20) #=> 0.69314718055994530942e0
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @since 0.1.0
 */
static VALUE
const_math_log2(VALUE unused_obj, VALUE prec)
{
	return rb_bigmath_const_log2(prec);
}

static VALUE
calc_log10(VALUE prec)
{
	return rb_bigmath_log(INT2FIX(10), prec);
}

static VALUE
math_log10_set_inline(VALUE prec)
{
	return rb_gv_set(BIGMATH_LOG10, calc_log10(prec));
}

VALUE
rb_bigmath_const_log10(VALUE prec)
{
	static int def_prec = DEF_PREC;
	VALUE m_log10 = rb_gv_get(BIGMATH_LOG10);
	prec = init_prec(prec);
	if (def_prec < NUM2INT(prec))
	{
		def_prec = NUM2LONG(prec);
		m_log10 = math_log10_set_inline(INT2FIX(def_prec));
	}

	if (NIL_P(m_log10))
		m_log10 = math_log10_set_inline(INT2FIX(def_prec));

        return rb_bigmath_round_inline(m_log10, prec);
}

/**
 * The natural logarithm of 10.
 * @example
 *  BigMathR.LOG10(20) #=> 
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @since 0.1.0
 */
static VALUE
const_math_log10(VALUE unused_obj, VALUE prec)
{
	return rb_bigmath_const_log10(prec);
}

static VALUE
calc_sqrt2(VALUE prec)
{
	const ID sqrt = rb_intern("sqrt");
	return rb_funcall(rb_BigDecimal1(INT2FIX(2)), sqrt, 1, prec);
}

static VALUE
math_sqrt2_set_inline(VALUE prec)
{
	return rb_gv_set(BIGMATH_SQRT2, calc_sqrt2(prec));
}

VALUE
rb_bigmath_const_sqrt2(VALUE prec)
{
	static int def_prec = DEF_PREC;
	VALUE m_sqrt2 = rb_gv_get(BIGMATH_SQRT2);
	prec = init_prec(prec);
	if (def_prec < NUM2INT(prec))
	{
		def_prec = NUM2LONG(prec);
		m_sqrt2 = math_sqrt2_set_inline(INT2FIX(def_prec));
	}

	if (NIL_P(m_sqrt2))
		m_sqrt2 = math_sqrt2_set_inline(INT2FIX(def_prec));
	
        return rb_bigmath_round_inline(m_sqrt2, prec);
}


/**
 * The square root of 2.
 * @example
 *  BigMathR.SQRT2(20) #=> 0.14142135623730950488e1
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @since 0.1.0
 */
static VALUE
const_math_sqrt2(VALUE unused_obj, VALUE prec)
{
	return rb_bigmath_const_sqrt2(prec);
}


static VALUE
calc_sqrt3(VALUE prec)
{
	const ID sqrt = rb_intern("sqrt");
        return rb_funcall(rb_BigDecimal1(INT2FIX(3)), sqrt, 1, prec);
}

static VALUE
math_sqrt3_set_inline(VALUE prec)
{
	return rb_gv_set(BIGMATH_SQRT3, calc_sqrt3(prec));
}

VALUE
rb_bigmath_const_sqrt3(VALUE prec)
{
	static int def_prec = DEF_PREC;
	VALUE m_sqrt3 = rb_gv_get(BIGMATH_SQRT3);
	prec = init_prec(prec);
	if (def_prec < NUM2INT(prec))
	{
		def_prec = NUM2LONG(prec);
		m_sqrt3 = math_sqrt3_set_inline(INT2FIX(def_prec));
	}

	if (NIL_P(m_sqrt3))
		m_sqrt3 = math_sqrt3_set_inline(INT2FIX(def_prec));
	
        return rb_bigmath_round_inline(m_sqrt3, prec);
}


/**
 * The square root of 3.
 * @example
 *  BigMathR.SQRT3(20) #=> 0.17320508075688772935e1
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @since 0.1.0
 */
static VALUE
const_math_sqrt3(VALUE unused_obj, VALUE prec)
{
	return rb_bigmath_const_sqrt3(prec);
}


/* :nodoc: */
void
InitVM_Constant(void)
{


	rb_gv_set(BIGMATH_PI, Qnil);
	rb_define_module_function(rb_mBigMathR, "PI", const_math_pi, 1);

	rb_gv_set(BIGMATH_E, Qnil);
	rb_define_module_function(rb_mBigMathR, "E", const_math_e, 1);

	rb_gv_set(BIGMATH_LOG2, Qnil);
	rb_define_module_function(rb_mBigMathR, "LOG2", const_math_log2, 1);

	rb_gv_set(BIGMATH_LOG10, Qnil);
	rb_define_module_function(rb_mBigMathR, "LOG10", const_math_log10, 1);

	rb_gv_set(BIGMATH_SQRT2, Qnil);
	rb_define_module_function(rb_mBigMathR, "SQRT2", const_math_sqrt2, 1);

	rb_gv_set(BIGMATH_SQRT3, Qnil);
	rb_define_module_function(rb_mBigMathR, "SQRT3", const_math_sqrt3, 1);


}

