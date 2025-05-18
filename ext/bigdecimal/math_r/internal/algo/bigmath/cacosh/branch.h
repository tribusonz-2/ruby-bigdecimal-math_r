VALUE
cacosh_branch(VALUE z, VALUE prec, bigmath_func1 cacosh_cb)
{
	int z_re_inf = rb_num_infinite_p(rb_num_real(z));
	int z_im_inf = rb_num_infinite_p(rb_num_imag(z));

	if (rb_num_nan_p(z))
		return rb_Complex(BIG_NAN, BIG_NAN);
	else if (z_re_inf || z_im_inf)
	{
		if (z_re_inf != 0 && z_im_inf == 0)
		{
			VALUE real = BIG_INF;
			VALUE imag = (z_re_inf == -1 && rb_num_zero_p(rb_num_imag(z))) ? 
				rb_bigmath_const_pi(prec) : BIG_ZERO;
			return rb_Complex(real, imag);
		}
		else if (z_re_inf == 0 && z_im_inf != 0)
		{
			VALUE real = BIG_INF;
			VALUE imag = BIG_ZERO;
			return rb_Complex(real, imag);
		}
		else if (z_re_inf == -1 && z_im_inf == 1)
			return rb_Complex(BIG_NAN, BIG_NAN);
		else
			return rb_Complex(BIG_ZERO, BIG_ZERO);
	}
	else
	{
		z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
		return cacosh_cb(z, prec);
	}
}
