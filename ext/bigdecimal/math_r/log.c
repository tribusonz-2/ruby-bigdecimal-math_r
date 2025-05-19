/*******************************************************************************
	log.c -- Logarithm

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"
#include "decl.h"

/**
 * Computes natural logarithm of +x + 1+ by mercator series expansion.
 * 
 * @example
 *  BigMathR::Log.log1p_ser_mercator(1, 20)
 *  #=> 0.69314718055994530942e0
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Real precision
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_log1p_ser_mercator(VALUE uunused_obj, VALUE x, VALUE prec)
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
			return log1p_ser_mercator(x, prec);
	}
	else
		return BIG_NAN;
}

/**
 * Computes p-adic logarithm of +x+.
 * 
 * @example
 *  BigMathR::Log.log1p_p_adic(1, 20)
 *  #=> 0.69314718055994530942e0
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Real precision
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_log1p_p_adic(VALUE uunused_obj, VALUE x, VALUE prec)
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
			return log1p_p_adic(x, prec);
	}
	else
		return BIG_NAN;
}

/**
 * Computes natural logarithm of +x+ by builtin function.
 * <br>
 * @example
 *  BigMathR::Log.log_builtin(2, 20)
 *  #=> 0.69314718055994530942e0
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_log_builtin(VALUE uunused_obj, VALUE x, VALUE prec)
{
	return log_branch(x, prec, log_builtin);
}

/**
 * Computes natural logarithm of +x+ by series expansion.
 * <br>
 * @example
 *  BigMathR::Log.log_ser_okumura(2, 20)
 *  #=> 0.69314718055994530942e0
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [TypeError] +prec+ is not an Integer
 * @raise [RangeError] +prec+ is zero or negative number
 * @since 0.1.0
 */
static VALUE
__impl_log_ser_okumura(VALUE uunused_obj, VALUE x, VALUE prec)
{
	return log_branch(x, prec, log_ser_okumura);
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
__impl_log_edf(VALUE unused_obj, VALUE x, VALUE prec)
{
	return log_branch(x, prec, log_edf);
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
__impl_log2_edf(VALUE unused_obj, VALUE x, VALUE prec)
{
	return log2_branch(x, prec, log2_edf);
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
__impl_log10_edf(VALUE unused_obj, VALUE x, VALUE prec)
{
	return log10_branch(x, prec, log10_edf);
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
__impl_clog_formula(VALUE unused_obj, VALUE z, VALUE prec)
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
__impl_clog2_formula(VALUE unused_obj, VALUE z, VALUE prec)
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
__impl_clog10_formula(VALUE unused_obj, VALUE z, VALUE prec)
{
	return clog_branch(z, prec, clog10_formula);
}


/**
 *  Document-module:  BigMathR::Logarithm
 *  
 *  A module that treats the logarithm algorithm.
 *  It is used internally.
 *  <br>
 *  == Synopsis
 *  The function names defined are the same as those in the C/C++ standard.
 *  <br>
 *  - Natural logarithm:                     +:clog+ <br>
 *  - Binary logarithm:                      +:clog2+ <br>
 *  - Common logarithm:                      +:clog10+ <br>
 */
void
InitVM_Log(void)
{
	rb_define_module_function(rb_mLog, "log_builtin", __impl_log_builtin, 2);
	rb_define_module_function(rb_mLog, "log_ser_okumura", __impl_log_ser_okumura, 2);

	rb_define_module_function(rb_mLog, "log_edf", __impl_log_edf, 2);
	rb_define_module_function(rb_mLog, "log2_edf", __impl_log2_edf, 2);
	rb_define_module_function(rb_mLog, "log10_edf", __impl_log10_edf, 2);

	rb_define_module_function(rb_mLog, "log1p_ser_mercator", __impl_log1p_ser_mercator, 2);
	rb_define_module_function(rb_mLog, "log1p_p_adic", __impl_log1p_p_adic, 2);

	rb_define_module_function(rb_mLog, "clog_formula", __impl_clog_formula, 2);
	rb_define_module_function(rb_mLog, "clog2_formula", __impl_clog2_formula, 2);
	rb_define_module_function(rb_mLog, "clog10_formula", __impl_clog10_formula, 2);
}
