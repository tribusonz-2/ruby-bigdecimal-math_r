/*******************************************************************************
	nucomp.c -- Complex Plane

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"
#include "decl.h"

/**
 * @overload l2norm(*args, prec)
 *  Return solve of the euclidean norm (L2-norm) for argument as numerical sequence.
 *  
 *  @param *args [Array] Numerical sequence
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +z+ is not a numeric class.
 *  @example
 *   BigMathR::ComplexPlane.l2norm(2, 4, 5, 20)
 *   #=> 0.670820393249936908923e1
 *  @since 0.1.0
 */
static VALUE
__impl_nucomp_l2norm(VALUE unused_obj, VALUE args)
{
	if (RARRAY_LEN(args) < 2)
		rb_raise(rb_eArgError, 
			"wrong number of arguments (given %ld, expected 2..)", 
			RARRAY_LEN(args));
	VALUE prec = rb_ary_pop(args);
	rb_check_precise(prec);
	return rb_bigmath_l2norm(args, prec);
}


/**
 *  Returns the hypotenuse of a right triangle with side lengths of +a+ and +b+.
 *  <br>
 *  The return value will definitely be a positive real number. 
 *  <br>
 *  It is implemented by the norm, 
 *  so even if the argument is a complex number, 
 *  it will be a positive real number.
 *  
 *  @param a [Numeric] adjacent side or opposite side
 *  @param b [Numeric] adjacent side or opposite side
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +x+ is not a numeric class.
 *  @since 0.1.0
 */
static VALUE
__impl_bigmathr_hypot(VALUE unused_obj, VALUE a, VALUE b, VALUE prec)
{
	return rb_bigmath_hypot(a, b, prec);
}

/**
 *  Return complex absolute of +z+.
 *  
 *  @param z [Numeric] Complex variable
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +z+ is not a numeric class.
 *  @since 0.1.0
 */
static VALUE
__impl_nucomp_cabs(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_bigmath_cabs(z, prec);
}

/**
 *  Consider where the value is in quadrant XY and computes the inverse tangent of +y/x+.
 *  
 *  @param x [Numeric] X-axis
 *  @param y [Numeric] Y-axis
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @return [Complex] Complex solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +x+ is not a numeric class.
 *  @since 0.1.0
 */
static VALUE
__impl_nucomp_quadrant(VALUE unused_obj, VALUE x, VALUE y, VALUE prec)
{
	return rb_bigmath_quadrant(x, y, prec);
}

/**
 *  Consider where the value is in quadrant XY and computes the inverse tangent of +y/x+.
 *  
 *  @param y [Numeric] Y-axis
 *  @param x [Numeric] X-axis
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @return [Complex] Complex solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +x+ is not a numeric class.
 *  @since 0.1.0
 */
static VALUE
__impl_bigmathr_atan2(VALUE unused_obj, VALUE y, VALUE x, VALUE prec)
{
	return rb_bigmath_quadrant(x, y, prec);
}

/**
 *  Return complex argument of +z+.
 *  
 *  @param z [Numeric] Complex variable
 *  @param prec [Integer] Arbitrary precision
 *  @return [BigDecimal] Real solution
 *  @raise [ArgumentError] Occurs when +prec+ is not a positive integer.
 *  @raise [TypeError] Occurs when +z+ is not a numeric class.
 *  @since 0.1.0
 */
static VALUE
__impl_nucomp_carg(VALUE unused_obj, VALUE z, VALUE prec)
{
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_bigmath_carg(z, prec);
}

/**
 *  Document-module:  BigMathR::ComplexPlane
 *  
 *  A module that provides whole of functions related to the complex plane. 
 *  It is used internally.
 *  <br>
 *  == Synopsis
 *  The function names defined are the same as those in the C/C++ standard.
 *  <br>
 *  - Complex argument:    +:carg+ <br>
 *  - Complex absolute:    +:cabs+ <br>
 *  Follow, the name defined in C/C++ standard though, the function names are different.
 *  <br>
 *  - Quadrant XY:         +:quadrant+ ( +:atan2+ in C/C++ ) <br>
 */
void
InitVM_ComplexPlane(void)
{
	rb_define_module_function(rb_mComplexPlane, "l2norm", __impl_nucomp_l2norm, -2);
	rb_define_module_function(rb_mComplexPlane, "cabs", __impl_nucomp_cabs, 2);
	rb_define_module_function(rb_mComplexPlane, "quadrant", __impl_nucomp_quadrant, 3);
	rb_define_module_function(rb_mComplexPlane, "carg", __impl_nucomp_carg, 2);

	rb_define_module_function(rb_mBigMathR, "hypot", __impl_bigmathr_hypot, 3);
	rb_define_module_function(rb_mBigMathR, "atan2", __impl_bigmathr_atan2, 3);

}
