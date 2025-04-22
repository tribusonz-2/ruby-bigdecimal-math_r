/*******************************************************************************
	euler_f.c -- Euler's formula

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
 *  BigMathR::EulerF.cexp(1+1i, 20)
 *  #=> (0.14686939399158851572e1+0.22873552871788423912e1i)
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_cexp(VALUE unused_obj, VALUE z, VALUE prec)
{
	return cexp_eulerf(z, prec);
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
 *  BigMathR::EulerF.cexp2(1+1i, 20)
 *  #=> (0.15384778027279442532e1+0.12779225526272696023e1i)
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_cexp2(VALUE unused_obj, VALUE z, VALUE prec)
{
	return cexp2_eulerf(z, prec);
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
 *  BigMathR::EulerF.sin(1, 20)
 *  #=> 0.84147098480789650665e0
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_sin(VALUE unused_obj, VALUE x, VALUE prec)
{
	return sin_eulerf(x, prec);
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
 *  BigMathR::EulerF.cos(1, 20)
 *  #=> 0.5403023058681397174e0
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_cos(VALUE unused_obj, VALUE x, VALUE prec)
{
	return cos_eulerf(x, prec);
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
 *  BigMathR::EulerF.tan(1, 20)
 *  #=> 0.15574077246549022305e1
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_tan(VALUE unused_obj, VALUE x, VALUE prec)
{
	return tan_eulerf(x, prec);
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
 *  BigMathR::EulerF.csc(1, 20)
 *  #=> 0.11883951057781212163e1
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_csc(VALUE unused_obj, VALUE x, VALUE prec)
{
	return csc_eulerf(x, prec);
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
 *  BigMathR::EulerF.sec(1, 20)
 *  #=> 0.18508157176809256179e1
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_sec(VALUE unused_obj, VALUE x, VALUE prec)
{
	return sec_eulerf(x, prec);
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
 *  BigMathR::EulerF.cot(1, 20)
 *  #=> 0.64209261593433070301e0
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_cot(VALUE unused_obj, VALUE x, VALUE prec)
{
	return cot_eulerf(x, prec);
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
 *  BigMathR::EulerF.csin(1+1i, 20)
 *  #=> (0.12984575814159772948e1+0.63496391478473610827e0i)
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_csin(VALUE unused_obj, VALUE z, VALUE prec)
{
	return csin_eulerf(z, prec);
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
 *  BigMathR::EulerF.ccos(1+1i, 20)
 *  #=> (0.83373002513114904889e0-0.9888977057628650964e0i)
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_ccos(VALUE unused_obj, VALUE z, VALUE prec)
{
	return ccos_eulerf(z, prec);
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
 *  BigMathR::EulerF.ctan(1+1i, 20)
 *  #=> (0.27175258531951171652e0+0.10839233273386945435e1i)
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_ctan(VALUE unused_obj, VALUE z, VALUE prec)
{
	return ctan_eulerf(z, prec);
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
 *  BigMathR::EulerF.ccsc(1+1i, 20)
 *  #=> (0.62151801717042842124e0-0.30393100162842645035e0i)
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_ccsc(VALUE unused_obj, VALUE z, VALUE prec)
{
	return ccsc_eulerf(z, prec);
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
 *  BigMathR::EulerF.csec(1+1i, 20)
 *  #=> (0.4983370305551867852e0+0.59108384172104504804e0i)
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_csec(VALUE unused_obj, VALUE z, VALUE prec)
{
	return csec_eulerf(z, prec);
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
 *  BigMathR::EulerF.ccot(1+1i, 20)
 *  #=> (0.21762156185440268135e0-0.86801414289592494862e0i)
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_ccot(VALUE unused_obj, VALUE z, VALUE prec)
{
	return ccot_eulerf(z, prec);
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
 *  BigMathR::EulerF.sinh(1, 20)
 *  #=> 0.11752011936438014569e1
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_sinh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return sinh_eulerf(x, prec);
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
 *  BigMathR::EulerF.cosh(1, 20)
 *  #=> 0.15430806348152437785e1
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_cosh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return cosh_eulerf(x, prec);
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
 *  BigMathR::EulerF.tanh(1, 20)
 *  #=> 0.76159415595576488813e0
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_tanh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return tanh_eulerf(x, prec);
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
 *  BigMathR::EulerF.csch(1, 20)
 *  #=> 0.85091812823932154512e0
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_csch(VALUE unused_obj, VALUE x, VALUE prec)
{
	return csch_eulerf(x, prec);
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
 *  BigMathR::EulerF.sech(1, 20)
 *  #=> 0.64805427366388539957e0
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_sech(VALUE unused_obj, VALUE x, VALUE prec)
{
	return sech_eulerf(x, prec);
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
 *  BigMathR::EulerF.coth(1, 20)
 *  #=> 0.13130352854993313036e1
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_coth(VALUE unused_obj, VALUE x, VALUE prec)
{
	return coth_eulerf(x, prec);
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
 *  BigMathR::EulerF.csinh(1+1i, 20)
 *  #=> (0.63496391478473610827e0+0.12984575814159772948e1i)
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_csinh(VALUE unused_obj, VALUE z, VALUE prec)
{
	return csinh_eulerf(z, prec);
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
 *  BigMathR::EulerF.ccosh(1+1i, 20)
 *  #=> (0.83373002513114904889e0+0.9888977057628650964e0i)
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_ccosh(VALUE unused_obj, VALUE z, VALUE prec)
{
	return ccosh_eulerf(z, prec);
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
 *  BigMathR::EulerF.ctanh(1+1i, 20)
 *  #=> (0.10839233273386945435e1+0.27175258531951171652e0i)
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_ctanh(VALUE unused_obj, VALUE z, VALUE prec)
{
	return ctanh_eulerf(z, prec);
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
 *  BigMathR::EulerF.ccsch(1+1i, 20)
 *  #=> (0.30393100162842645035e0-0.62151801717042842124e0i)
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_ccsch(VALUE unused_obj, VALUE z, VALUE prec)
{
	return ccsch_eulerf(z, prec);
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
 *  BigMathR::EulerF.csech(1+1i, 20)
 *  #=> (0.4983370305551867852e0-0.59108384172104504804e0i)
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_csech(VALUE unused_obj, VALUE z, VALUE prec)
{
	return csech_eulerf(z, prec);
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
 *  BigMathR::EulerF.ccoth(1+1i, 20)
 *  #=> (0.86801414289592494862e0-0.21762156185440268135e0i)
 * @since 0.1.0
 */
static VALUE
__impl_eulerf_ccoth(VALUE unused_obj, VALUE z, VALUE prec)
{
	return ccoth_eulerf(z, prec);
}

/**
 *  Document-module:  BigMathR::EulerF
 *  
 *  A module that provides using Euler's formula. 
 *  It is used internally.
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
InitVM_EulerF(void)
{
	rb_define_module_function(rb_mEulerF, "cexp", __impl_eulerf_cexp, 2);
	rb_define_module_function(rb_mEulerF, "cexp2", __impl_eulerf_cexp2, 2);

	rb_define_module_function(rb_mEulerF, "sin", __impl_eulerf_sin, 2);
	rb_define_module_function(rb_mEulerF, "cos", __impl_eulerf_cos, 2);
	rb_define_module_function(rb_mEulerF, "tan", __impl_eulerf_tan, 2);
	rb_define_module_function(rb_mEulerF, "csc", __impl_eulerf_csc, 2);
	rb_define_module_function(rb_mEulerF, "sec", __impl_eulerf_sec, 2);
	rb_define_module_function(rb_mEulerF, "cot", __impl_eulerf_cot, 2);

	rb_define_module_function(rb_mEulerF, "csin", __impl_eulerf_csin, 2);
	rb_define_module_function(rb_mEulerF, "ccos", __impl_eulerf_ccos, 2);
	rb_define_module_function(rb_mEulerF, "ctan", __impl_eulerf_ctan, 2);
	rb_define_module_function(rb_mEulerF, "ccsc", __impl_eulerf_ccsc, 2);
	rb_define_module_function(rb_mEulerF, "csec", __impl_eulerf_csec, 2);
	rb_define_module_function(rb_mEulerF, "ccot", __impl_eulerf_ccot, 2);

	rb_define_module_function(rb_mEulerF, "sinh", __impl_eulerf_sinh, 2);
	rb_define_module_function(rb_mEulerF, "cosh", __impl_eulerf_cosh, 2);
	rb_define_module_function(rb_mEulerF, "tanh", __impl_eulerf_tanh, 2);
	rb_define_module_function(rb_mEulerF, "csch", __impl_eulerf_csch, 2);
	rb_define_module_function(rb_mEulerF, "sech", __impl_eulerf_sech, 2);
	rb_define_module_function(rb_mEulerF, "coth", __impl_eulerf_coth, 2);

	rb_define_module_function(rb_mEulerF, "csinh", __impl_eulerf_csinh, 2);
	rb_define_module_function(rb_mEulerF, "ccosh", __impl_eulerf_ccosh, 2);
	rb_define_module_function(rb_mEulerF, "ctanh", __impl_eulerf_ctanh, 2);
	rb_define_module_function(rb_mEulerF, "ccsch", __impl_eulerf_ccsch, 2);
	rb_define_module_function(rb_mEulerF, "csech", __impl_eulerf_csech, 2);
	rb_define_module_function(rb_mEulerF, "ccoth", __impl_eulerf_ccoth, 2);
}
