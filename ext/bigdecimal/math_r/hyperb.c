/*******************************************************************************
	hyperb.c -- Hyperbolic functions

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"
#include "decl.h"



/**
 *  Computes hyperbolic sine of +x+.
 *  
 *  @param x [Numeric] Numerical argument
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +x+ is not a numeric class.
 *  @since 0.1.0
 */
static VALUE
__impl_hyperb_sinh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return sinh_branch(x, prec, sinh_exp_identity);
}


/**
 *  Computes hyperbolic cosine of +x+.
 *  
 *  @param x [Numeric] Numerical argument
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +x+ is not a numeric class.
 *  @since 0.1.0
 */
static VALUE
__impl_hyperb_cosh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return cosh_branch(x, prec, cosh_exp_identity);
}

/**
 *  Computes hyperbolic tangent of +x+.
 *  
 *  @param x [Numeric] Numerical argument
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +x+ is not a numeric class.
 *  @since 0.1.0
 */
static VALUE
__impl_hyperb_tanh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return tanh_branch(x, prec, tanh_exp_identity);
}
 
/**
 *  Computes hyperbolic cosecant of +x+.
 *  
 *  @param x [Numeric] Numerical argument
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +x+ is not a numeric class.
 *  @since 0.1.0
 */

/**
 *  Computes hyperbolic secant of +x+.
 *  
 *  @param x [Numeric] Numerical argument
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +x+ is not a numeric class.
 *  @since 0.1.0
 */

/**
 *  Computes hyperbolic cotangent of +x+.
 *  @param x [Numeric] Numerical argument
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +x+ is not a numeric class.
 *  @since 0.1.0
 */



/**
 *  Document-module: BigMathR::Hyperb
 *  
 *  A module that provides a hyperbolic functions.
 *  It is used internally.
 */
void
InitVM_Hyperb(void)
{
	rb_define_singleton_method(rb_mHyperb, "sinh", __impl_hyperb_sinh, 2);
	rb_define_singleton_method(rb_mHyperb, "cosh", __impl_hyperb_cosh, 2);
	rb_define_singleton_method(rb_mHyperb, "tanh", __impl_hyperb_tanh, 2);
}
