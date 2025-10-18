VALUE
casinh_branch(VALUE z, VALUE prec, bigmath_func1 casinh_cb)
{
	VALUE y = Qundef;

	int z_re_inf = rb_num_infinite_p(rb_num_real(z));
	int z_im_inf = rb_num_infinite_p(rb_num_imag(z));

	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);

	if (rb_num_nan_p(z))
		y = rb_Complex(BIG_NAN, BIG_NAN);
	else if (!rb_num_finite_p(z))
	{
		if (z_re_inf != 0 && z_im_inf == 0)
		{
			switch (z_re_inf) {
			case 1:
				y = rb_Complex(BIG_INF, BIG_ZERO);
				break;
			case -1:
				y = rb_Complex(BIG_MINUS_INF, BIG_ZERO);
				break;
			}
		}
		else if (z_re_inf == 0 && z_im_inf != 0)
		{
			const ID div = rb_intern("div");
			VALUE pi_2 = rb_funcall(rb_bigmath_const_pi(prec), div, 2, INT2FIX(2), prec);
			switch (z_im_inf) {
			case 1:
				y = rb_Complex(BIG_INF, pi_2);
				break;
			case -1:
				pi_2 = rb_num_uminus(pi_2);
				y = rb_Complex(BIG_INF, pi_2);
				break;
			}
		}
		else
		{
			VALUE real = BIG_INF;
			VALUE imag = BIG_NAN;
			if (z_re_inf == -1)
				real = rb_num_uminus(real);
			y = rb_Complex(real, imag);
		}
	}
	if (y == Qundef)
	{
		y = casinh_cb(z, prec);
	}
	return y;
}
