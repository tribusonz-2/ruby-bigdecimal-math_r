/*******************************************************************************
	log.c -- Logarithm

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"
#include "decl.h"



static VALUE
__impl_log_n_ser_okumura(VALUE uunused_obj, VALUE x, VALUE prec)
{
	// BUG: 循環小数だと誤差を拾うことがある。
	// BigMathR::Logarithm.ser_okumura(BigDecimal('5.0'), 1000) - BigMath.log(BigDecimal('5.0'), 1000)
	// #=> 0.18e-44
	// BigMathR::Logarithm.ser_okumura(BigDecimal('10'), 1000) - BigMath.log(BigDecimal('10'), 1000)
	// #=> 0.18e-44
	return log_branch(x, prec, log_ser_okumura);
}


static VALUE
__impl_log_n_ser_mercator(VALUE uunused_obj, VALUE x, VALUE prec)
{
	const ID cover_p = rb_intern("cover?");
	VALUE domain = rb_range_new(INT2FIX(-1), INT2FIX(1), false);
	if (RTEST(rb_funcall(domain, cover_p, 1, x)))
	{
		if (rb_num_equal_p(x, INT2FIX(-1)))
			return BIG_MINUS_INF;
		else if (rb_num_equal_p(x, INT2FIX(1)))
			return rb_bigmath_const_log2(prec);
		else
			return log_ser_mercator(x, prec);
	}
	else
		return BIG_NAN;
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
__impl_log_clog(VALUE unused_obj, VALUE z, VALUE prec)
{
	return clog_branch(z, prec, clog_formula);
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
__impl_log_clog2(VALUE unused_obj, VALUE z, VALUE prec)
{
	return clog_branch(z, prec, clog2_formula);
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
__impl_log_clog10(VALUE unused_obj, VALUE z, VALUE prec)
{
	return clog_branch(z, prec, clog10_formula);
}


/**
 *  Document-module:  BigMathR::Logarithm
 *  
 *  A module that treats the logarithm algorithm.
 *  It is used internally.
 *  <br>
 */
void
InitVM_Log(void)
{
	rb_define_module_function(rb_mLog, "n_ser_okumura", __impl_log_n_ser_okumura, 2);
	rb_define_module_function(rb_mLog, "n_ser_mercator", __impl_log_n_ser_mercator, 2);

	rb_define_module_function(rb_mLog, "clog", __impl_log_clog, 2);
	rb_define_module_function(rb_mLog, "clog2", __impl_log_clog2, 2);
	rb_define_module_function(rb_mLog, "clog10", __impl_log_clog10, 2);
}
