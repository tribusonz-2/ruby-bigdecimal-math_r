VALUE
casin_branch(VALUE z, VALUE prec, bigmath_func1 casin_cb)
{
	int z_re_inf = rb_num_infinite_p(rb_num_real(z));
	int z_im_inf = rb_num_infinite_p(rb_num_imag(z));

	if (rb_num_nan_p(z))
		return rb_Complex(BIG_NAN, BIG_NAN);
	else if (z_re_inf || z_im_inf)
	{
		const ID div = rb_intern("div");
		const ID mult = rb_intern("mult");
		VALUE real, imag;
		if (z_re_inf != 0 && z_im_inf == 0)
		{
			real = 
				rb_funcall(rb_bigmath_const_pi(prec), div, 2, 
					INT2FIX(z_re_inf * 2), prec);
			imag = z_re_inf == 1 ? BIG_MINUS_INF : BIG_INF;
			return rb_Complex(real, imag);
		}
		else if (z_re_inf == 0 && z_im_inf != 0)
		{
			real = rb_bigmath_const_pi(prec);
			imag = BIG_MINUS_INF;
			if (z_im_inf == -1)
				real = rb_funcall(real, div, 2, INT2FIX(2), prec);
			return rb_Complex(real, imag);
		}
		else
		{
			VALUE rat = Qundef;
			real = rb_bigmath_const_pi(prec);
			imag = BIG_MINUS_INF;
			if (z_re_inf == 1 && z_im_inf == 1)
				rat = rb_rational_new(INT2FIX(5), INT2FIX(4));
			else if (z_re_inf == 1 && z_im_inf == -1)
				rat = rb_rational_new(INT2FIX(3), INT2FIX(4));
			else
				rat = rb_rational_new(INT2FIX(1), INT2FIX(4));
			real = rb_funcall(real, mult, 2, rat, prec);
			return rb_Complex(real, imag);
		}
	}
	else
	{
		z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
		return casin_cb(z, prec);
	}
}
