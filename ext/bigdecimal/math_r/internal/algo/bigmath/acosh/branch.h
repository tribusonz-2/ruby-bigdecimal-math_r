VALUE
acosh_branch(VALUE x, VALUE prec, bigmath_func1 acosh_cb)
{
	VALUE y = Qundef;
	VALUE domain = rb_range_new(INT2FIX(1), DBL2NUM(HUGE_VAL), false);

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	if (rb_num_positive_p(x))
	{
		if (rb_num_infinite_p(x) == 1)
			y = BIG_INF;
		else if (rb_num_domain_p(domain, x))
			y = acosh_cb(x, prec);
	}
	if (y == Qundef)
		y = BIG_NAN;

	return y;
}
