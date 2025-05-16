/*******************************************************************************
	erf.c -- Error function

	Author: tribusonz
	License: MIT
*******************************************************************************/
#include <ruby.h>
#include "math_r/globals.h"
#include "math_r/bigmath_r.h"
#include "decl.h"


static VALUE
__impl_erf_erf_algo911(VALUE unused_obj, VALUE x, VALUE prec)
{
	return erf_branch(x, prec, erf_algo911);
}

static VALUE
__impl_erf_erfc_algo911(VALUE unused_obj, VALUE x, VALUE prec)
{
	return erfc_branch(x, prec, erfc_algo911);
}


void
InitVM_Erf(void)
{
	rb_define_singleton_method(rb_mErf, "erf_algo911", __impl_erf_erf_algo911, 2);
	rb_define_singleton_method(rb_mErf, "erfc_algo911", __impl_erf_erfc_algo911, 2);
}
