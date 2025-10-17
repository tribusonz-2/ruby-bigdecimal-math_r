VALUE
cacos_branch(VALUE z, VALUE prec, bigmath_func1 cacos_cb)
{
	const ID mult = rb_intern("mult");
	const ID div = rb_intern("div");
	int z_re_inf = rb_num_infinite_p(rb_num_real(z));
	int z_im_inf = rb_num_infinite_p(rb_num_imag(z));

	if (rb_num_nan_p(z))
		return rb_Complex(BIG_NAN, BIG_NAN);
	else if (z_re_inf || z_im_inf)
	{
		if (z_re_inf != 0 && z_im_inf == 0)
		{
			VALUE real = 
				(rb_num_zero_p(rb_num_imag(z)) &&
			         z_re_inf == 1) ?
				BIG_ZERO : rb_bigmath_const_pi(prec);
			VALUE imag = BIG_MINUS_INF;
			return rb_Complex(real, imag);
		}
		else if (z_re_inf == 0 && z_im_inf != 0)
		{
			VALUE real = rb_bigmath_const_pi(prec);
			VALUE imag = z_im_inf == 1 ? BIG_MINUS_INF : BIG_INF;
			if (!rb_num_negative_p(rb_num_real(z)))
				real = rb_funcall(real, div, 2, INT2FIX(2), prec);
			return rb_Complex(real, imag);
		}
		else
		{
			VALUE real = rb_bigmath_const_pi(prec);
			VALUE imag = z_im_inf == -1 ? BIG_INF : BIG_MINUS_INF;
			real = z_re_inf == -1 ?
				rb_funcall(real, mult, 2, 
					rb_rational_new(INT2FIX(3), INT2FIX(4)), prec) :
				rb_funcall(real, div, 2, INT2FIX(4), prec);
			return rb_Complex(real, imag);
		}
	}
	else
	{
		z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
		return cacos_cb(z, prec);
	}
}
