/*******************************************************************************
	erf.c -- Error function

	Author: tribusonz
	License: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"
#include "decl.h"

/**
 * Calculate the error function of +x+.
 * 
 * @param x [Numeric] Numerical Argument.
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [FloatDomainError] Numerical arguments are out of range
 * @example
 *  BigMathR::Erf.erf_algo911(7, 20)
 *  #=> 0.1e1
 *  BigMathR::Erf.erf_algo911(7, 40)
 *  #=> 0.999999999999999999999958161743922205856e0
 * @since 0.2.0
 */
static VALUE
__impl_erf_erf_algo911(VALUE unused_obj, VALUE x, VALUE prec)
{
	return erf_branch(x, prec, erf_algo911);
}

/**
 * Calculate the complementary error function of +x+.
 * 
 * @param x [Numeric] Numerical Argument.
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [FloatDomainError] Numerical arguments are out of range
 * @example
 *  BigMathR::Erf.erfc_algo911(-7, 20)
 *  #=> 0.2e1
 *  BigMathR::Erf.erfc_algo911(-7, 40) 
 *  #=> 0.1999999999999999999999958161743922205856e1
 *  BigMathR::Erf.erfc_algo911(7, 20)
 *  #=> 0.0
 *  BigMathR::Erf.erfc_algo911(7, 40)
 *  #=> 0.41838256077794144e-22
 * @since 0.2.0
 */
static VALUE
__impl_erf_erfc_algo911(VALUE unused_obj, VALUE x, VALUE prec)
{
	return erfc_branch(x, prec, erfc_algo911);
}

/**
 * Document-module: BigMathR::Erf
 * 
 * A module that provides an eror functions.
 * It is used internally.
 * <br>
 * == Synopsis
 * Some functions are common in the C/C++ standard. 
 * However, it is not actually defined in C/C++, and is specified in POSIX.
 * <br>
 * - Error function:                 +:erf+ <br>
 * - Complementary Error function:   +:erfc+ <br>
 * The following are complex functions that are reserved words mainly for Linux OS.
 * <br>
 * - Error function:                 +:cerf+ <br>
 * - Complementary Error function:   +:cerfc+ <br>
 * Reference::
 * Multiple-Precision Exponential Integral and Related Functions - David M. Smith
 */
void
InitVM_Erf(void)
{
	rb_define_singleton_method(rb_mErf, "erf_algo911", __impl_erf_erf_algo911, 2);
	rb_define_singleton_method(rb_mErf, "erfc_algo911", __impl_erf_erfc_algo911, 2);
}
