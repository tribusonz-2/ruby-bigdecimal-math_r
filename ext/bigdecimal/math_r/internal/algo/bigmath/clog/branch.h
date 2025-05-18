VALUE
clog_branch(VALUE z, VALUE prec, bigmath_func1 clog_cb)
{
	VALUE w = Qundef, arg = Qundef;

	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);

	if (!rb_num_finite_p(z))
	{
		if (rb_num_notequal_p(z, z))
		{
			w = rb_Complex(BIG_NAN, BIG_NAN);
		}
		else if (rb_num_finite_p(rb_num_imag(z)))
		{
			switch (rb_num_infinite_p(rb_num_real(z))) {
			case -1:
				arg = rb_num_imag(clog_cb(BIG_MINUS_ONE, prec));
				w = rb_Complex(BIG_INF, arg);
				break;
			case 1:
				w = rb_Complex(BIG_INF, BIG_ZERO);
				break;
			}
		}
		else if (rb_num_finite_p(rb_num_real(z)))
		{
			switch (rb_num_infinite_p(rb_num_imag(z))) {
			case -1:
				arg = rb_num_imag(
					clog_cb(rb_Complex(BIG_ZERO, BIG_MINUS_ONE), prec));
				w = rb_Complex(BIG_INF, arg);
				break;
			case 1:
				arg = rb_num_imag(
					clog_cb(rb_Complex(BIG_ZERO, BIG_ONE), prec));
				w = rb_Complex(BIG_INF, arg);
				break;
			}
		}
		else /* log(INF +i INF) */
		{
			w = rb_Complex(
				rb_BigDecimal1(rb_num_real(z)),
				rb_BigDecimal1(rb_num_imag(z))
			);
		}
	}
	if (w == Qundef)
	{
		w = clog_cb(z, prec);
	}
	return w;
}
