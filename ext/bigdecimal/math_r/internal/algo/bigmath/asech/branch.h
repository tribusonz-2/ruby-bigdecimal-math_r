VALUE
asech_branch(VALUE x, VALUE prec, bigmath_func1 asech_cb)
{
	const ID leq = rb_intern("<=");
	VALUE y;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (RTEST(rb_num_coerce_cmp(BIG_ZERO, x, leq)) &&
	    RTEST(rb_num_coerce_cmp(x, BIG_ONE, leq)))
	{
		y = asech_cb(x, prec);
	}
	else
		y = BIG_NAN;

	return y;
}
