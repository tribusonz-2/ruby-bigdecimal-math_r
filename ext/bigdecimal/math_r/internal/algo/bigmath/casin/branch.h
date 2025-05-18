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
		if (z_re_inf != 0 && z_im_inf == 0)
		{
			VALUE real = rb_num_zero_p(rb_num_imag(z)) ?
				rb_funcall(rb_bigmath_const_pi(prec), div, 2, 
					INT2FIX(z_re_inf * 2), prec) :
				BIG_ZERO;
			VALUE imag = z_re_inf == 1 ? BIG_MINUS_INF : BIG_INF;
			return rb_Complex(real, imag);
		}
		else if (z_re_inf == 0 && z_im_inf != 0)
		{
			return rb_Complex(BIG_ZERO, rb_num_imag(z));
		}
		else if (z_re_inf == -1 && z_im_inf == 1)
			return rb_Complex(BIG_NAN, BIG_NAN);
		else
			return rb_Complex(BIG_ZERO, BIG_ZERO);
	}
	else
	{
		z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
		return casin_cb(z, prec);
	}
}
