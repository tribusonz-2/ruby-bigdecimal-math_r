/*******************************************************************************
	numeric.c -- API for Numeric

	Author: tribusonz
	Licence: MIT
*******************************************************************************/
#include <ruby.h>
#include "internal/solver/bigmath_r.h"

VALUE
rb_num_uminus(VALUE x)
{
	const ID uminus = rb_intern("-@");
	return rb_funcall(x, uminus, 0);
}


VALUE
rb_num_real(VALUE z)
{
	const ID real = rb_intern("real");
	return rb_funcall(z, real, 0);
}


VALUE
rb_num_imag(VALUE z)
{
	const ID imag = rb_intern("imag");
	return rb_funcall(z, imag, 0);
}



bool
rb_num_positive_p(VALUE z)
{
	const ID positive_p = rb_intern("positive?");
	return RTEST(rb_funcall(z, positive_p, 0));
}


bool
rb_num_negative_p(VALUE z)
{
	const ID negative_p = rb_intern("negative?");
	return RTEST(rb_funcall(z, negative_p, 0));
}


bool
rb_num_equal_p(VALUE lhs, VALUE rhs)
{
	const ID equal = rb_intern("==");
	return RTEST(rb_num_coerce_cmp(lhs, rhs, equal));
}


bool
rb_num_notequal_p(VALUE lhs, VALUE rhs)
{
	const ID notequal = rb_intern("!=");
	return RTEST(rb_num_coerce_cmp(lhs, rhs, notequal));
}


VALUE
rb_num_cmpeql(VALUE lhs, VALUE rhs)
{
	const ID cmpeql = rb_intern("<=>");
	return rb_num_coerce_cmp(lhs, rhs, cmpeql);
}


bool
rb_num_zero_p(VALUE z)
{
	const ID zero_p = rb_intern("zero?");
	return RTEST(rb_funcall(z, zero_p, 0));
}


bool
rb_num_nonzero_p(VALUE z)
{
	const ID nonzero_p = rb_intern("nonzero?");
	return RTEST(rb_funcall(z, nonzero_p, 0));
}


bool
rb_num_real_p(VALUE z)
{
	const ID real_p = rb_intern("real?");
	return RTEST(rb_funcall(z, real_p, 0));
}


bool
rb_num_finite_p(VALUE z)
{
	const ID finite_p = rb_intern("finite?");
	return RTEST(rb_funcall(z, finite_p, 0));
}


int
rb_num_infinite_p(VALUE z)
{
	const ID infinite_p = rb_intern("infinite?");
	VALUE y = rb_funcall(z, infinite_p, 0);
	return NIL_P(y) ? 0 : NUM2INT(y);
}

bool
rb_num_nan_p(VALUE z)
{
	return (!rb_num_finite_p(z) && !rb_num_infinite_p(z));
}

VALUE
rb_ImaginaryZ(VALUE z, bool signbit)
{
	VALUE real, imag;
	real = signbit ? rb_num_imag(z) : rb_num_uminus(rb_num_imag(z));
	imag = signbit ? rb_num_uminus(rb_num_real(z)) : rb_num_real(z);
	return rb_Complex(real, imag);
}
