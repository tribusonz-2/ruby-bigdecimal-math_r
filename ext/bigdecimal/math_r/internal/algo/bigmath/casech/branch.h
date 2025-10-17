VALUE
casech_branch(VALUE z, VALUE prec, bigmath_func1 casech_cb)
{
	VALUE w = Qundef;
	int z_re_inf = rb_num_infinite_p(rb_num_real(z));
	int z_im_inf = rb_num_infinite_p(rb_num_imag(z));

	if (rb_num_nan_p(z))
		w = rb_Complex(BIG_NAN, BIG_NAN);
	else if (z_re_inf || z_im_inf)
	{
		const ID div = rb_intern("div");
		if ((z_re_inf != 0 && z_im_inf == 0) ||
		    (z_re_inf == 0 && z_im_inf != 0))
		{
			VALUE imag = rb_funcall(rb_bigmath_const_pi(prec), div, 
				2, INT2FIX(2), prec);
			w = rb_Complex(BIG_ZERO, imag);
		}
		else
			w = rb_Complex(BIG_ZERO, BIG_ZERO);
	}
	else
	{
		z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
		w = casech_cb(z, prec);
	}

	return w;
}
