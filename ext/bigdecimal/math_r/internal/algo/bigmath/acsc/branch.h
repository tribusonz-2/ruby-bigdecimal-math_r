VALUE
acsc_branch(VALUE x, VALUE prec, bigmath_func1 acsc_cb)
{
	const ID leq = rb_intern("<=");
	const ID geq = rb_intern(">=");
	VALUE y = Qundef;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (rb_num_nan_p(x))
		y = BIG_NAN;
	else if (rb_num_infinite_p(x) != 0)
		y = BIG_ONE;
	else if (RTEST(rb_num_coerce_bin(x, INT2FIX(-1), leq)) ||
	         RTEST(rb_num_coerce_bin(x, INT2FIX( 1), geq)))
		y = acsc_cb(x, prec);
	else
		y = BIG_NAN;

	return y;
}
