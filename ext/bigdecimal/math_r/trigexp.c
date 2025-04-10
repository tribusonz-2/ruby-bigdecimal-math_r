/*******************************************************************************
	trigexp.c -- Trigonometry & Exponent (Euler's formula)

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"
#include "decl.h"


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
__impl_trigexp_cexp(VALUE unused_obj, VALUE z, VALUE prec)
{
	return cexp_f_euler(z, prec);
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
__impl_trigexp_cexp2(VALUE unused_obj, VALUE z, VALUE prec)
{
	return cexp2_f_euler(z, prec);
}

/**
 * Computes sine of +x+.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.sin(1, 20)
 *  #=> 0.84147098480789650665e0
 * @since 0.1.0
 */
static VALUE
__impl_trigexp_sin(VALUE unused_obj, VALUE x, VALUE prec)
{
	return sin_f_euler(x, prec);
}

/**
 * Computes cosine of +x+.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.cos(1, 20)
 *  #=> 0.5403023058681397174e0
 * @since 0.1.0
 */
static VALUE
__impl_trigexp_cos(VALUE unused_obj, VALUE x, VALUE prec)
{
	return cos_f_euler(x, prec);
}

/**
 * Computes tangent of +x+.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.tan(1, 20)
 *  #=> 0.15574077246549022305e1
 * @since 0.1.0
 */
static VALUE
__impl_trigexp_tan(VALUE unused_obj, VALUE x, VALUE prec)
{
	return tan_f_euler(x, prec);
}

/**
 * Computes cosecant of +x+.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.csc(1, 20)
 *  #=> 0.11883951057781212163e1
 * @since 0.1.0
 */
static VALUE
__impl_trigexp_csc(VALUE unused_obj, VALUE z, VALUE prec)
{
	return csc_f_euler(z, prec);
}

/**
 * Computes secant of +x+.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.sec(1, 20)
 *  #=> 0.18508157176809256179e1
 * @since 0.1.0
 */
static VALUE
__impl_trigexp_sec(VALUE unused_obj, VALUE x, VALUE prec)
{
	return sec_f_euler(x, prec);
}

/**
 * Computes cotangent of +x+.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::TrigExp.cot(1, 20)
 *  #=> 0.64209261593433070301e0
 * @since 0.1.0
 */
static VALUE
__impl_trigexp_cot(VALUE unused_obj, VALUE z, VALUE prec)
{
	return cot_f_euler(z, prec);
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
__impl_trigexp_csin(VALUE unused_obj, VALUE z, VALUE prec)
{
	return csin_f_euler(z, prec);
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
__impl_trigexp_ccos(VALUE unused_obj, VALUE z, VALUE prec)
{
	return ccos_f_euler(z, prec);
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
__impl_trigexp_ctan(VALUE unused_obj, VALUE z, VALUE prec)
{
	return ctan_f_euler(z, prec);
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
__impl_trigexp_ccsc(VALUE unused_obj, VALUE z, VALUE prec)
{
	return ccsc_f_euler(z, prec);
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
__impl_trigexp_csec(VALUE unused_obj, VALUE z, VALUE prec)
{
	return csec_f_euler(z, prec);
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
 *  BigMathR::TrigExp.ccot(1+1i, 20)
 *  #=> (0.21762156185440268135e0-0.86801414289592494862e0i)
 * @since 0.1.0
 */
static VALUE
__impl_trigexp_ccot(VALUE unused_obj, VALUE z, VALUE prec)
{
	return ccot_f_euler(z, prec);
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
__impl_trigexp_sinh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return sinh_f_euler(x, prec);
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
__impl_trigexp_cosh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return cosh_f_euler(x, prec);
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
__impl_trigexp_tanh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return tanh_f_euler(x, prec);
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
__impl_trigexp_csch(VALUE unused_obj, VALUE x, VALUE prec)
{
	return csch_f_euler(x, prec);
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
__impl_trigexp_sech(VALUE unused_obj, VALUE x, VALUE prec)
{
	return sech_f_euler(x, prec);
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
__impl_trigexp_coth(VALUE unused_obj, VALUE x, VALUE prec)
{
	return coth_f_euler(x, prec);
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
__impl_trigexp_csinh(VALUE unused_obj, VALUE z, VALUE prec)
{
	return csinh_f_euler(z, prec);
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
__impl_trigexp_ccosh(VALUE unused_obj, VALUE z, VALUE prec)
{
	return ccosh_f_euler(z, prec);
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
__impl_trigexp_ctanh(VALUE unused_obj, VALUE z, VALUE prec)
{
	return ctanh_f_euler(z, prec);
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
__impl_trigexp_ccsch(VALUE unused_obj, VALUE z, VALUE prec)
{
	return ccsch_f_euler(z, prec);
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
__impl_trigexp_csech(VALUE unused_obj, VALUE z, VALUE prec)
{
	return csech_f_euler(z, prec);
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
__impl_trigexp_ccoth(VALUE unused_obj, VALUE z, VALUE prec)
{
	return ccoth_f_euler(z, prec);
}


/**
 *  Document-module:  BigMathR::TrigExp
 *  
 *  A module that provides using trigonometric and exponential function. 
 *  It is used internally.
 *  <br>
 *  "TrigExp" is, simply say, a module that uses Euler's formula.
 *  <br>
 *  By using this formula for complex analysis, 
 *  it can be applied to differential equations and Fourier transforms.
 *  <br>
 *  == Synopsis
 *  The function names defined are the same as those in the C/C++ standard.
 *  <br>
 *  - Exponential function:         +:cexp+ <br>
 *  - Base-2 (Binary) exponent:     +:cexp2+ <br>
 *  - Sine:                         +:csin+ <br>
 *  - Cosine:                       +:ccos+ <br>
 *  - Tangent:                      +:ctan+ <br>
 *  - Hyperbolic sine:      +:sinh+ +:csinh+ <br>
 *  - Hyperbolic cosine:    +:cosh+ +:ccosh+ <br>
 *  - Hyperbolic tangent:   +:tanh+ +:ctanh+ <br>
 *  Follow, those reciprocals of not defined in C/C++ standard.
 *  <br>
 *  - Cosecant:                     +:ccsc+ <br>
 *  - Secant:                       +:csec+ <br>
 *  - Cotangent:                    +:ccot+ <br>
 *  - Hyperbolic cosecant:  +:csch+ +:ccsch+ <br>
 *  - Hyperbolic secant:    +:sech+ +:csech+ <br>
 *  - Hyperbolic cotangent: +:coth+ +:ccoth+ <br>
 *  Reference::
 *  Kiso kara hatten made Sankaku kansuu (Japanese) - Michimasa Kobayashi (Beret Shuppan)
 */
void
InitVM_TrigExp(void)
{
	rb_define_module_function(rb_mTrigExp, "cexp", __impl_trigexp_cexp, 2);
	rb_define_module_function(rb_mTrigExp, "cexp2", __impl_trigexp_cexp2, 2);

	rb_define_module_function(rb_mTrigExp, "sin", __impl_trigexp_sin, 2);
	rb_define_module_function(rb_mTrigExp, "cos", __impl_trigexp_cos, 2);
	rb_define_module_function(rb_mTrigExp, "tan", __impl_trigexp_tan, 2);
	rb_define_module_function(rb_mTrigExp, "csc", __impl_trigexp_csc, 2);
	rb_define_module_function(rb_mTrigExp, "sec", __impl_trigexp_sec, 2);
	rb_define_module_function(rb_mTrigExp, "cot", __impl_trigexp_cot, 2);

	rb_define_module_function(rb_mTrigExp, "csin", __impl_trigexp_csin, 2);
	rb_define_module_function(rb_mTrigExp, "ccos", __impl_trigexp_ccos, 2);
	rb_define_module_function(rb_mTrigExp, "ctan", __impl_trigexp_ctan, 2);
	rb_define_module_function(rb_mTrigExp, "ccsc", __impl_trigexp_ccsc, 2);
	rb_define_module_function(rb_mTrigExp, "csec", __impl_trigexp_csec, 2);
	rb_define_module_function(rb_mTrigExp, "ccot", __impl_trigexp_ccot, 2);

	rb_define_module_function(rb_mTrigExp, "sinh", __impl_trigexp_sinh, 2);
	rb_define_module_function(rb_mTrigExp, "cosh", __impl_trigexp_cosh, 2);
	rb_define_module_function(rb_mTrigExp, "tanh", __impl_trigexp_tanh, 2);
	rb_define_module_function(rb_mTrigExp, "csch", __impl_trigexp_csch, 2);
	rb_define_module_function(rb_mTrigExp, "sech", __impl_trigexp_sech, 2);
	rb_define_module_function(rb_mTrigExp, "coth", __impl_trigexp_coth, 2);

	rb_define_module_function(rb_mTrigExp, "csinh", __impl_trigexp_csinh, 2);
	rb_define_module_function(rb_mTrigExp, "ccosh", __impl_trigexp_ccosh, 2);
	rb_define_module_function(rb_mTrigExp, "ctanh", __impl_trigexp_ctanh, 2);
	rb_define_module_function(rb_mTrigExp, "ccsch", __impl_trigexp_ccsch, 2);
	rb_define_module_function(rb_mTrigExp, "csech", __impl_trigexp_csech, 2);
	rb_define_module_function(rb_mTrigExp, "ccoth", __impl_trigexp_ccoth, 2);
}
