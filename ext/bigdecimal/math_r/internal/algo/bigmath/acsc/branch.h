VALUE
acsc_branch(VALUE x, VALUE prec, bigmath_func1 acsc_cb)
{
	VALUE y = Qundef;
	VALUE p_domain = rb_range_new(INT2FIX(1), DBL2NUM(HUGE_VAL), false);
	VALUE m_domain = rb_range_new(DBL2NUM(-HUGE_VAL), INT2FIX(-1), true);

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (rb_num_nan_p(x))
		y = BIG_NAN;
	else if (rb_num_infinite_p(x) != 0)
		y = BIG_ONE;
	else if (rb_num_domain_p(p_domain, x) || rb_num_domain_p(m_domain, x))
		y = acsc_cb(x, prec);
	else
		y = BIG_NAN;

	return y;
}
