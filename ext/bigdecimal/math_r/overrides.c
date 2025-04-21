/*******************************************************************************
	overrides.c -- Overriddem Methods

	Author: tribusonz
	License: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"
#include "decl.h"

/**
 * The #nan? method for primitive. Always return false.
 * 
 * @example
 *  1.nan? #=> false
 * @return [false] Whether self is Not a Number(NaN).
 */
static VALUE
numeric_nan_p(VALUE self)
{
	return Qfalse;
}

/**
 * Calculates "i z" so inverts the real and imaginary maps of +z+.
 * 
 * @example
 *  Complex.imaginary_z(1+2i) #=> (-2+1i)
 *  -Complex.imaginary_z(1+2i) #=> (2-1i)
 * @param z [Numeric] Numerical argument
 * @return [Complex] Solve
 */
static VALUE
__impl_nucomp_s_imaginary_z(VALUE self, VALUE z)
{
	return rb_ImaginaryZ(z, SIGN_PLUS);
}

/**
 * Returns a boolean whether the object is a numeric class.
 * 
 * @example
 *  1.numeric? #=> true
 *  1.0.numric? #=> true
 *  (1+1i).numeric? #=> true
 *  (1/3r).numeric? #=> true
 *  nil.numeric? #=> false
 *  "1.0".numeric? #=> false
 * @return [bool] Whether +self+ is a numeric class
 */
static VALUE
__impl_obj_numeric_p(VALUE self)
{
	return rb_num_numeric_p(self) ? Qtrue : Qfalse;
}

void
InitVM_Overrides(void)
{
	rb_define_method(rb_cNumeric, "nan?", numeric_nan_p, 0);
	rb_define_singleton_method(rb_cComplex, "imaginary_z", __impl_nucomp_s_imaginary_z, 1);
	rb_define_method(rb_cObject, "numeric?", __impl_obj_numeric_p, 0);
}
