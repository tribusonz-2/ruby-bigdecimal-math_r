/*******************************************************************************
	trig.c -- Trigonometric Function

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"
#include "decl.h"


/**
 * Computes at once sine and cosine of +x+.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Array] Real solutions [sin(x), cos(x)]
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::Trig.sincos(1, 20)
 *  #=> [0.84147098480789650665e0, 0.5403023058681397174e0]
 * @since 0.1.0
 */
static VALUE
__impl_trig_sincos(VALUE unused_obj, VALUE x, VALUE prec)
{
	VALUE sin, cos, t;
	rb_check_precise(prec);
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	x = rb_bigmath_to_rad(x, prec, &t);
	if (-1 == rb_bigmath_degree_sparg(t, prec, &sin, &cos))
		rb_bigmath_sincos(x, prec, &sin, &cos);
	sin = rb_num_round(sin, prec);
	cos = rb_num_round(cos, prec);
	return rb_assoc_new(sin, cos);
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
 *  BigMathR::Trig.sin(1, 20)
 *  #=> 0.84147098480789650665e0
 * @since 0.1.0
 */
static VALUE
__impl_trig_sin(VALUE unused_obj, VALUE x, VALUE prec)
{
	return sin_branch(x, prec, sin_ser);
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
 *  BigMathR::Trig.cos(1, 20)
 *  #=> 0.5403023058681397174e0
 * @since 0.1.0
 */
static VALUE
__impl_trig_cos(VALUE unused_obj, VALUE x, VALUE prec)
{
	return cos_branch(x, prec, cos_ser);
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
 *  BigMathR::Trig.tan(1, 20)
 *  #=> 0.15574077246549022305e1
 * @since 0.1.0
 */
static VALUE
__impl_trig_tan(VALUE unused_obj, VALUE x, VALUE prec)
{
	return tan_branch(x, prec, tan_ser);
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
 *  BigMathR::Trig.csc(1, 20)
 *  #=> 0.11883951057781212163e1
 * @since 0.1.0
 */
static VALUE
__impl_trig_csc(VALUE unused_obj, VALUE x, VALUE prec)
{
	return csc_branch(x, prec, csc_ser);
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
 *  BigMathR::Trig.sec(1, 20)
 *  #=> 0.18508157176809256179e1
 * @since 0.1.0
 */
static VALUE
__impl_trig_sec(VALUE unused_obj, VALUE x, VALUE prec)
{
	return sec_branch(x, prec, sec_ser);
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
 *  BigMathR::Trig.cot(1, 20)
 *  #=> 0.64209261593433070301e0
 * @since 0.1.0
 */
static VALUE
__impl_trig_cot(VALUE unused_obj, VALUE x, VALUE prec)
{
	return cot_branch(x, prec, cot_ser);
}

/**
 * Document-module: BigMathR::Trig
 * 
 * A module that provide the trigonometric functions.
 * It is used internally.
 * <br>
 * All module functions are implemented by +:sincos+.
 * <br>
 * == Synopsis
 * The function names defined are the same as those in the C/C++ standard.
 * <br>
 * - Sine:                +:sin+ <br>
 * - Cosine:              +:cos+ <br>
 * - Tangent:             +:tan+ <br>
 * Follow, those reciprocals of not defined in C/C++ standard.
 * <br>
 * - Cosecant:            +:csc+ <br>
 * - Secant:              +:sec+ <br>
 * - Cotangent:           +:cot+ <br>
 * The following are GNU extensions:
 * <br>
 * - sincos():            +:sincos+ <br>
 * Reference::
 * Kiso kara hatten made Sankaku kansuu (Japanese) - Michimasa Kobayashi (Beret Shuppan)
 */
void
InitVM_Trig(void)
{
	rb_define_module_function(rb_mTrig, "sincos", __impl_trig_sincos, 2);
	rb_define_module_function(rb_mTrig, "sin", __impl_trig_sin, 2);
	rb_define_module_function(rb_mTrig, "cos", __impl_trig_cos, 2);
	rb_define_module_function(rb_mTrig, "tan", __impl_trig_tan, 2);
	rb_define_module_function(rb_mTrig, "csc", __impl_trig_csc, 2);
	rb_define_module_function(rb_mTrig, "sec", __impl_trig_sec, 2);
	rb_define_module_function(rb_mTrig, "cot", __impl_trig_cot, 2);
}
