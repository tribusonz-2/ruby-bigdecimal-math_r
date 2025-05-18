VALUE
clog1p_branch(VALUE z, VALUE prec, bigmath_func1 clog1p_cb)
{
	VALUE w = Qundef;
	VALUE one_thousand = rb_Rational(INT2FIX(1), INT2FIX(1000));
	const ID geq = rb_intern_const(">=");

	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);

	if (!rb_num_finite_p(z))
	{
		if (rb_num_nan_p(z))
			w = rb_Complex(BIG_NAN, BIG_NAN);
		else
			w = clog_branch(z, prec, clog1p_cb);
	}
	if (w == Qundef)
	{
		if (rb_num_zero_p(z))
			w = rb_Complex(BIG_ZERO, BIG_ZERO);
		else if (RTEST(rb_num_coerce_cmp(one_thousand, rb_bigmath_cabs(z, prec), geq)))
		{
			w = clog1p_cb(z, prec);
			if (rb_num_real_p(w))
				w = rb_Complex(w, BIG_ZERO);
		}
		else
		{
			z = rb_funcall1(z, '+', BIG_ONE);
			w = rb_bigmath_clog(z, prec);
		}
	}
	return w;
}
