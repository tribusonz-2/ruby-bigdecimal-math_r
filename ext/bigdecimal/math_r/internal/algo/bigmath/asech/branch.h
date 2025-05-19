VALUE
asech_branch(VALUE x, VALUE prec, bigmath_func1 asech_cb)
{
	VALUE y;
	VALUE domain = rb_range_new(INT2FIX(0), INT2FIX(1), false);

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (rb_num_domain_p(domain, x))
		y = asech_cb(x, prec);
	else
		y = BIG_NAN;

	return y;
}
