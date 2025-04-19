VALUE
clog_branch(VALUE z, VALUE prec, bigmath_func1 clog_cb)
{
	const ID div = rb_intern("div");
	VALUE w = Qundef, pi = Qundef;
	rb_check_precise(prec);
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
				pi = rb_bigmath_const_pi(prec);
				w = rb_Complex(BIG_INF, pi);
				break;
			case 1:
				w = rb_Complex(BIG_INF, BIG_ZERO);
				break;
			}
		}
		else if (rb_num_finite_p(rb_num_real(z)))
		{
			pi = rb_bigmath_const_pi(prec);
			pi = rb_funcall(pi, div, 2, INT2FIX(2), prec);
			switch (rb_num_infinite_p(rb_num_imag(z))) {
			case -1:
				w = rb_Complex(BIG_INF, rb_num_uminus(pi));
				break;
			case 1:
				w = rb_Complex(BIG_INF, pi);
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
		if (clog_cb != NULL)
			w = clog_cb(z, prec);
		else
			w = BIG_NAN;
	}
	return w;
}
