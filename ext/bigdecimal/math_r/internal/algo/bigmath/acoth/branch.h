VALUE
acoth_branch(VALUE x, VALUE prec, bigmath_func1 acoth_cb)
{
	VALUE y;
	const ID leq = rb_intern("<=");

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (rb_num_equal_p(x, BIG_ONE))
		y = BIG_INF;
	else if (rb_num_equal_p(x, BIG_MINUS_ONE))
		y = BIG_MINUS_INF;
	else if (RTEST(rb_num_coerce_cmp(x, BIG_MINUS_ONE, leq)) ||
	         RTEST(rb_num_coerce_cmp(BIG_ONE, x, leq)))
		y = acoth_cb(x, prec);
	else
		y = BIG_NAN;

	return y;
}
