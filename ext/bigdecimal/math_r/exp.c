/******************************************************************************
	exp.c -- Exponential Functions

	Author: tribusonz
	Lisence: MIT
******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"
#include "decl.h"

/**
 * Computes exponential function of +x+.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::Exp.exp_edf(1, 20)
 *  #=> 0.27182818284590452354e1
 * @since 0.1.0
 */
static VALUE
__impl_exp_edf(VALUE unused_obj, VALUE x, VALUE prec)
{
	return exp_branch(x, prec, exp_edf);
}


/**
 * Computes binary exponent of +x+.
 * 
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::Exp.exp2_edf(1/2r, 20)
 *  #=> 0.14142135623730950488e1
 * @since 0.1.0
 */
static VALUE
__impl_exp2_edf(VALUE unused_obj, VALUE x, VALUE prec)
{
	return exp2_branch(x, prec, exp2_edf);
}

/**
 * Computes the subtracted 1 from x of the exponential function.
 * <br>
 * The calculation is more accurate than +exp(x)-1+ when the argument is near zero.
 * @param x [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +x+ is not a numeric class.
 * @example
 *  BigMathR::Exp.expm1_identity(BigDecimal(1), 20)
 *  #=> 0.17182818284590452354e1
 * @since 0.2.2
 */
static VALUE
__impl_expm1_identity(VALUE unused_obj, VALUE x, VALUE prec)
{
	return expm1_branch(x, prec, expm1_identity);
}

/**
 * Computes the subtracted 1 from +z+ of the exponential function.
 * 
 * @param z [Numeric] Numerical argument
 * @param prec [Integer] Arbitrary precision
 * @return [Complex] Complex solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @raise [TypeError] Occurs when +z+ is not a numeric class.
 * @example
 *  BigMathR::Exp.cexpm1_identity(1+1i, 20)
 *  # => (0.46869393991588515714e0+0.22873552871788423912e1i)
 * @since 0.2.2
 */
static VALUE
__impl_cexpm1_identity(VALUE unused_obj, VALUE z, VALUE prec)
{
	return cexpm1_branch(z, prec, cexpm1_identity);
}



/**
 *  Document-module:  BigMathR::Exp
 *  
 *  A module that treats the exponential functions.
 *  It is used internally.
 *  <br>
 *  This formula was discovered by the author shortly afterwards. It will be proven in time.
 *  <br>
 *  == Synopsis:
 *  The function names defined are the same as those in the C/C++ standard.
 *  <br>
 *  Exponential function:     +exp()+ <br>
 *  Base-2 (binary) exponent: +exp2()+ <br>
 *  expm1 function:           +expm1()+ <br>
 */
void
InitVM_Exp(void)
{
	rb_define_module_function(rb_mExp, "exp_edf", __impl_exp_edf, 2);
	rb_define_module_function(rb_mExp, "exp2_edf", __impl_exp2_edf, 2);
	rb_define_module_function(rb_mExp, "expm1_identity", __impl_expm1_identity, 2);
	rb_define_module_function(rb_mExp, "cexpm1_identity", __impl_cexpm1_identity, 2);
}
