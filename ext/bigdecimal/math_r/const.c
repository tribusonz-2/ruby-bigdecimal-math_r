/*******************************************************************************
	constant.c -- Mathematical constants

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"
#include "decl.h"

/**
 * The constant pi.
 * @example
 *  BigMathR.PI(20) #=> 0.314159265358979323846e1
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @since 0.1.0
 */
static VALUE
__impl_const_pi(VALUE unused_obj, VALUE prec)
{
	return rb_bigmath_const_pi(prec);
}

/**
 * The natural logarithm of pi.
 * @example
 *  BigMathR.LOG_PI(20) #=> 0.11447298858494001741e1
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @since 0.1.0
 */
static VALUE
__impl_const_log_pi(VALUE unused_obj, VALUE prec)
{
	return rb_bigmath_const_log_pi(prec);
}

/**
 * The constant e.
 * @example
 *  BigMathR.E(20) #=> 0.27182818284590452354e1
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @since 0.1.0
 */
static VALUE
__impl_const_e(VALUE unused_obj, VALUE prec)
{
	return rb_bigmath_const_e(prec);
}

/**
 * The natural logarithm of 2.
 * @example
 *  BigMathR.LOG2(20) #=> 0.69314718055994530942e0
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @since 0.1.0
 */
static VALUE
__impl_const_log2(VALUE unused_obj, VALUE prec)
{
	return rb_bigmath_const_log2(prec);
}

/**
 * The natural logarithm of 10.
 * @example
 *  BigMathR.LOG10(20) #=> 0.2302585092994045684e1
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @since 0.1.0
 */
static VALUE
__impl_const_log10(VALUE unused_obj, VALUE prec)
{
	return rb_bigmath_const_log10(prec);
}

/**
 * The square root of 2.
 * @example
 *  BigMathR.SQRT2(20) #=> 0.14142135623730950488e1
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @since 0.1.0
 */
static VALUE
__impl_const_sqrt2(VALUE unused_obj, VALUE prec)
{
	return rb_bigmath_const_sqrt2(prec);
}

/**
 * The square root of 3.
 * @example
 *  BigMathR.SQRT3(20) #=> 0.17320508075688772935e1
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Real solution
 * @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 * @since 0.1.0
 */
static VALUE
__impl_const_sqrt3(VALUE unused_obj, VALUE prec)
{
	return rb_bigmath_const_sqrt3(prec);
}

/**
 * Implement by Machin's formula.
 * 
 * @example
 *  BigMathR::Const::PI.machin(20)
 *  #=> 0.31415926535897932385e1
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Constant PI
 * @raise [TypeError] not an Integer
 * @raise [RangeError] Zero or negative precision
 */
static VALUE
__impl_const_pi_machin(VALUE unused_obj, VALUE prec)
{
	return PI_machin(prec);
}

/**
 * Implement by series expansion: sum_(n=0)^infty 1/n!
 * 
 * @example
 *  BigMathR::Const::E.napier(20)
 *  #=> 0.27182818284590452354e1
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Natural logarithm of 2
 * @raise [TypeError] not an Integer
 * @raise [RangeError] Zero or negative precision
 */
static VALUE
__impl_const_e_napier(VALUE unused_obj, VALUE prec)
{
	return E_napier(prec);
}

/**
 * Implement by BBP's formula (Borwein and Bailey 2002)
 * 
 * @example
 *  BigMathR::Const::LOG2.bbp2002(20)
 *  #=> 0.69314718055994530942e0
 * @param prec [Integer] Arbitrary precision
 * @return [BigDecimal] Natural logarithm of 2
 * @raise [TypeError] not an Integer
 * @raise [RangeError] Zero or negative precision
 */
static VALUE
__impl_const_log2_bbp2002(VALUE unused_obj, VALUE prec)
{
	return LOG2_BBP2002(prec);
}


/* :nodoc: */
void
InitVM_Const(void)
{
	rb_define_module_function(rb_mBigMathR, "PI", __impl_const_pi, 1);
	rb_define_module_function(rb_mBigMathR, "E", __impl_const_e, 1);
	rb_define_module_function(rb_mBigMathR, "LOG2", __impl_const_log2, 1);
	rb_define_module_function(rb_mBigMathR, "LOG_PI", __impl_const_log_pi, 1);
	rb_define_module_function(rb_mBigMathR, "LOG10", __impl_const_log10, 1);
	rb_define_module_function(rb_mBigMathR, "SQRT2", __impl_const_sqrt2, 1);
	rb_define_module_function(rb_mBigMathR, "SQRT3", __impl_const_sqrt3, 1);

	rb_define_module_function(rb_mConstPI, "machin", __impl_const_pi_machin, 1);
	rb_define_module_function(rb_mConstE, "napier", __impl_const_e_napier, 1);
	rb_define_alias(rb_mConstE, "euler_number", "napier");
	rb_define_module_function(rb_mConstLOG2, "bbp2002", __impl_const_log2_bbp2002, 1);

}

