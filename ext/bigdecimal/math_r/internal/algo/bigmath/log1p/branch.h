VALUE
log1p_branch(VALUE x, VALUE prec, bigmath_func1 log1p_cb)
{
	VALUE y = Qundef;
	VALUE one_thousand = rb_Rational(INT2FIX(1), INT2FIX(1000)), n;
	const ID geq = rb_intern_const(">=");
	const ID gt = rb_intern_const(">");

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (!rb_num_finite_p(x))
	{
		if (rb_num_nan_p(x))
			y = BIG_NAN;
		else
			y = log_branch(x, prec, log1p_cb);
	}
	if (y == Qundef)
	{
		if (rb_num_zero_p(x))
			y = BIG_ZERO;
		else if (RTEST(rb_num_coerce_cmp(one_thousand, rb_num_abs(x), geq)))
			y = log1p_cb(x, prec);
		else if (RTEST(rb_num_coerce_cmp(INT2FIX(-1), x, gt)))
			y = BIG_NAN;
		else
		{
			rb_check_precise(prec);
			n = rb_numdiff_make_n(prec);

			x = rb_funcall1(x, '+', BIG_ONE);
			y = rb_bigmath_log(x, n);
			y = rb_num_round(y, prec);
		}
	}
	return y;
}
