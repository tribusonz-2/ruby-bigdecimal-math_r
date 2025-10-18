VALUE
catanh_branch(VALUE z, VALUE prec, bigmath_func1 catanh_cb)
{
	VALUE w = Qundef;
	int z_re_inf = rb_num_infinite_p(rb_num_real(z));
	int z_im_inf = rb_num_infinite_p(rb_num_imag(z));

	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);

	if (rb_num_nan_p(z))
		w = rb_Complex(BIG_NAN, BIG_NAN);
	else if (z_re_inf || z_im_inf)
	{
		if (z_re_inf != 0 && z_im_inf != 0)
			w = rb_Complex(BIG_NAN, BIG_NAN);
		else
		{
			const ID div = rb_intern("div");
			VALUE pi_2 = rb_funcall(
				rb_bigmath_const_pi(prec), div, 2, INT2FIX(2), prec);
			if (z_re_inf == 1 || z_im_inf == -1)
				pi_2 = rb_num_uminus(pi_2);
			w = rb_Complex(BIG_ZERO, pi_2);
		}
	}
	else
	{
		z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
		w = catanh_cb(z, prec);
	}

	return w;
}
