VALUE
clog10_branch(VALUE z, VALUE prec, bigmath_func1 clog10_cb)
{
	VALUE w = Qundef, arg = Qundef;

	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);

	if (rb_num_nan_p(z))
	{
		w = rb_Complex(BIG_NAN, BIG_NAN);
	}
	else if (!rb_num_finite_p(z))
	{
		int re_inf_sgn = rb_num_infinite_p(rb_num_real(z));
		int im_inf_sgn = rb_num_infinite_p(rb_num_imag(z));
		if (re_inf_sgn != 0 && im_inf_sgn == 0)
		{
			switch (re_inf_sgn) {
			case -1:
				arg = rb_num_imag(clog10_cb(BIG_MINUS_ONE, prec));
				w = rb_Complex(BIG_INF, arg);
				break;
			case 1:
				w = rb_Complex(BIG_INF, BIG_ZERO);
				break;
			}
		}
		else if (re_inf_sgn == 0 && im_inf_sgn != 0)
		{
			switch (rb_num_infinite_p(rb_num_imag(z))) {
			case -1:
				arg = rb_num_imag(
					clog10_cb(rb_Complex(BIG_ZERO, BIG_MINUS_ONE), prec));
				w = rb_Complex(BIG_INF, arg);
				break;
			case 1:
				arg = rb_num_imag(
					clog10_cb(rb_Complex(BIG_ZERO, BIG_ONE), prec));
				w = rb_Complex(BIG_INF, arg);
				break;
			}
		}
		else /* log(INF +i INF) */
		{
			w = z;
		}
	}
	if (w == Qundef)
	{
		w = clog10_cb(z, prec);
	}
	return w;
}
