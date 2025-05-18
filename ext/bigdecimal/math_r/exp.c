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
 *  BigMathR::EDF.exp(1, 20)
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
 *  BigMathR::EDF.exp2(1/2r, 20)
 *  #=> 0.14142135623730950488e1
 * @since 0.1.0
 */
static VALUE
__impl_exp2_edf(VALUE unused_obj, VALUE x, VALUE prec)
{
	return exp2_branch(x, prec, exp2_edf);
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
 *  
 */
void
InitVM_Exp(void)
{
	rb_define_module_function(rb_mExp, "exp_edf", __impl_exp_edf, 2);
	rb_define_module_function(rb_mExp, "exp2_edf", __impl_exp2_edf, 2);
}
