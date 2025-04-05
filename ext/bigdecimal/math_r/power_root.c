/*******************************************************************************
	power_root.c -- Power Root

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"
#include "decl.h"

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
__impl_powerroot_sqrt(VALUE unused_obj, VALUE x, VALUE prec)
{
	VALUE y;
	y = rb_bigmath_sqrt(x, prec);
	return rb_num_round(y, prec);
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
__impl_powerroot_csqrt(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
        return csqrt_formula(z, prec);
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
__impl_powerroot_cuberoot(VALUE unused_obj, VALUE x, VALUE prec)
{
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return cuberoot_newton(x, prec);
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
__impl_powerroot_ccbrt(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
        return ccbrt_formula(z, prec);
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
	rb_define_module_function(rb_mPowerRoot, "sqrt", __impl_powerroot_sqrt, 2);
	rb_define_module_function(rb_mPowerRoot, "csqrt", __impl_powerroot_csqrt, 2);
	rb_define_module_function(rb_mPowerRoot, "cuberoot", __impl_powerroot_cuberoot, 2);
	rb_define_module_function(rb_mPowerRoot, "ccbrt", __impl_powerroot_ccbrt, 2);
}
