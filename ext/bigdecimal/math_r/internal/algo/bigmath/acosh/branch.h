VALUE
acosh_branch(VALUE x, VALUE prec, bigmath_func1 acosh_cb)
{
	const ID geq = rb_intern(">=");
	VALUE y = Qundef;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	if (rb_num_positive_p(x))
	{
		if (rb_num_infinite_p(x) == 1)
			y = BIG_INF;
		else if (RTEST(rb_num_coerce_cmp(x, BIG_ONE, geq)))
			y = acosh_cb(x, prec);
	}
	if (y == Qundef)
		y = BIG_NAN;

	return y;
}
