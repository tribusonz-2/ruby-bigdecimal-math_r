VALUE
casec_branch(VALUE z, VALUE prec, bigmath_func1 casec_cb)
{
	int z_re_inf = rb_num_infinite_p(rb_num_real(z));
	int z_im_inf = rb_num_infinite_p(rb_num_imag(z));

	if (rb_num_nan_p(z))
	{
		return rb_Complex(BIG_NAN, BIG_NAN);
	}
	else if (z_re_inf || z_im_inf)
	{
		return rb_Complex(BIG_ZERO, BIG_ZERO);
	}
	else if (rb_num_zero_p(z))
	{
		int zero_sign = NUM2INT(rb_BigDecimal_sign(rb_num_real(z)));
		VALUE real = 
			(rb_num_nonzero_p(rb_num_imag(z)) || zero_sign == -1) ?
			BIG_ZERO : rb_bigmath_const_pi(prec);
		VALUE imag = 1 == zero_sign ? BIG_MINUS_INF : BIG_INF;
		return rb_Complex(real, imag);
	}
	else
	{
		z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
		return casec_cb(z, prec);
	}
}
