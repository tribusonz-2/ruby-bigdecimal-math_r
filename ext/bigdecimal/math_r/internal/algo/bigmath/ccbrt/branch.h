VALUE
ccbrt_branch(VALUE z, VALUE prec, bigmath_func1 ccbrt_cb)
{
	VALUE w = Qundef;

	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);

	if (rb_num_nan_p(z))
	{
		w = rb_Complex(BIG_NAN, BIG_NAN);
	}
	else if (!rb_num_finite_p(z))
	{
		int re_sgn = rb_num_infinite_p(rb_num_real(z));
		int im_sgn = rb_num_infinite_p(rb_num_imag(z));
		if (re_sgn != 0 && im_sgn == 0)
		{
			switch (re_sgn) {
			case 1:
				w = rb_Complex1(BIG_INF);
				break;
			case -1:
				w = rb_Complex(BIG_ZERO, BIG_INF);
				break;
			}
		}
		else
		{
			w = rb_Complex(
				BIG_INF,
				rb_num_coerce_bin(im_sgn, BIG_INF, '*')
			);
		}
	}
	if (w == Qundef)
	{
		w = ccbrt_cb(z, prec);
	}
	return w;
}
