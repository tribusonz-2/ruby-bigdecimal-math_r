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
 * Computes hyperbolic sine of +x+.
 * 
 * @example
 *  BigMathR::Hyperb.sinh(1, 20) # Series expansion
 *  #=> 0.11752011936438014569e1
 *  BigMathR::Hyperb.sinh(4, 20) # Exponent identity
 *  #=> 0.27289917197127752449e2
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @since 0.1.0
 */
static VALUE
__impl_hyperb_sinh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return sinh_branch(x, prec, sinh_exp_identity);
}


/**
 * Computes hyperbolic cosine of +x+.
 * 
 * @example
 *  BigMathR::Hyperb.cosh(1, 20) # Series expansion
 *  #=> 0.15430806348152437785e1
 *  BigMathR::Hyperb.cosh(4, 20) # Exponent identity
 *  #=> 0.27308232836016486629e2

 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @since 0.1.0
 */
static VALUE
__impl_hyperb_cosh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return cosh_branch(x, prec, cosh_exp_identity);
}

/**
 * Computes hyperbolic tangent of +x+.
 * 
 * @example
 *  BigMathR::Hyperb.tanh(1, 20) # Series expansion
 *  #=> 0.76159415595576488812e0
 *  BigMathR::Hyperb.tanh(4, 20) # Exponent identity
 *  #=> 0.99932929973906704379e0
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @since 0.1.0
 */
static VALUE
__impl_hyperb_tanh(VALUE unused_obj, VALUE x, VALUE prec)
{
	return tanh_branch(x, prec, tanh_exp_identity);
}
 
/**
 * Computes hyperbolic cosecant of +x+.
 * 
 * @example
 *  BigMathR::Hyperb.csch(1, 20) # Series expansion
 *  #=> 0.85091812823932154512e0
 *  BigMathR::Hyperb.csch(4, 20) # Exponent identity
 *  #=> 0.36643570325865605966e-1
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @since 0.1.0
 */
static VALUE
__impl_hyperb_csch(VALUE unused_obj, VALUE x, VALUE prec)
{
	return csch_branch(x, prec, csch_exp_identity);
}

/**
 * Computes hyperbolic secant of +x+.
 * 
 * @example
 *  BigMathR::Hyperb.sech(1, 20) # Series expansion
 *  #=> 0.64805427366388539957e0
 *  BigMathR::Hyperb.sech(4, 20) # Exponent identity
 *  #=> 0.36618993473686532773e-1
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @since 0.1.0
 */
static VALUE
__impl_hyperb_sech(VALUE unused_obj, VALUE x, VALUE prec)
{
	return sech_branch(x, prec, sech_exp_identity);
}

/**
 * Computes hyperbolic cotangent of +x+.
 * 
 * @example
 *  BigMathR::Hyperb.coth(1, 20) # Series expansion
 *  #=> 0.13130352854993313036e1
 *  BigMathR::Hyperb.coth(4, 20) # Exponent identity
 *  #=> 0.10006711504016824899e1
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @since 0.1.0
 */
static VALUE
__impl_hyperb_coth(VALUE unused_obj, VALUE x, VALUE prec)
{
	return coth_branch(x, prec, coth_exp_identity);
}


/**
 * Document-module: BigMathR::Hyperb
 * 
 * A module that provides a hyperbolic functions.
 * It is used internally.
 * <br>
 * It handle the real number solutions. 
 * The algorithm is implemented according to the references, 
 * when |x| < 3 computes to series expansion, otherwise computes by exponent identity.
 * == Synopsis
 * The function names defined are the same as those in the C/C++ standard.
 * <br>
 * - Hyperbolic Sine:                +:sinh+ <br>
 * - Hyperbolic Cosine:              +:cosh+ <br>
 * - Hyperbolic Tangent:             +:tanh+ <br>
 * Follow, those reciprocals of not defined in C/C++ standard.
 * <br>
 * - Hyperbolic Cosecant:            +:csch+ <br>
 * - Hyperbolic Secant:              +:sech+ <br>
 * - Hyperbolic Cotangent:           +:coth+ <br>
 * Reference::
 * C-gengo ni yoru hyoujun alkgorithm jiten (Japanese) - Hasruhiko Okumura (Gijutsu hyouron-sha)
 */
void
InitVM_Hyperb(void)
{
	rb_define_singleton_method(rb_mHyperb, "sinh", __impl_hyperb_sinh, 2);
	rb_define_singleton_method(rb_mHyperb, "cosh", __impl_hyperb_cosh, 2);
	rb_define_singleton_method(rb_mHyperb, "tanh", __impl_hyperb_tanh, 2);
	rb_define_singleton_method(rb_mHyperb, "csch", __impl_hyperb_csch, 2);
	rb_define_singleton_method(rb_mHyperb, "sech", __impl_hyperb_sech, 2);
	rb_define_singleton_method(rb_mHyperb, "coth", __impl_hyperb_coth, 2);
}
