VALUE
catan_branch(VALUE z, VALUE prec, bigmath_func1 catan_cb)
{
#define rb_Complex_I rb_Complex(INT2FIX(0), INT2FIX(1))
#define rb_Complex_mI rb_Complex(INT2FIX(0), INT2FIX(-1))
	int z_re_inf = rb_num_infinite_p(rb_num_real(z));
	int z_im_inf = rb_num_infinite_p(rb_num_imag(z));

	if (rb_num_nan_p(z))
		return rb_Complex(BIG_NAN, BIG_NAN);
	else if (z_re_inf || z_im_inf)
	{
		const ID mult = rb_intern("mult");
		const ID div = rb_intern("div");
		VALUE real, imag;
		if (z_re_inf != 0 && z_im_inf == 0)
		{
			real = rb_funcall(rb_bigmath_const_pi(prec), div, 2, 
				INT2FIX(z_re_inf * 2), prec);
			imag = BIG_ZERO;
			return rb_Complex(real, imag);
		}
		else if (z_re_inf == 0 && z_im_inf != 0)
		{
			real = rb_funcall(rb_bigmath_const_pi(prec), div, 2, 
				INT2FIX(z_im_inf * 2), prec);
			imag = BIG_ZERO;
			return rb_Complex(real, imag);
		}
		else
		{
			real = rb_funcall(rb_bigmath_const_pi(prec), mult, 2, 
				rb_rational_new(INT2FIX(z_im_inf * 3), INT2FIX(4)), prec);
			imag = BIG_ZERO;
			return rb_Complex(real, imag);
		}
	}
	else if (rb_num_equal_p(z, rb_Complex_I))
		return rb_Complex(BIG_ZERO, BIG_INF);
	else if (rb_num_equal_p(z, rb_Complex_mI))
		return rb_Complex(BIG_ZERO, BIG_MINUS_INF);
	else
	{
		z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
		return catan_cb(z, prec);
	}
#undef rb_Complex_I
#undef rb_Complex_mI
}
