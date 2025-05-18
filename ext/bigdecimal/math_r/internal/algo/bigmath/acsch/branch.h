VALUE
acsch_branch(VALUE x, VALUE prec, bigmath_func1 acsch_cb)
{
	const ID leq = rb_intern("<=");
	VALUE y = Qundef;
	int sign;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (rb_num_nan_p(x))
		y = BIG_NAN;
	else if ((sign = rb_num_infinite_p(x)) != 0)
	{
		y = sign == 1 ? BIG_ZERO : BIG_MINUS_ZERO;
	}
	else if (RTEST(rb_num_coerce_bin(x, BIG_MINUS_ONE, leq)) ||
	         RTEST(rb_num_coerce_bin(BIG_ONE, x, leq)))
	{
		y = acsch_cb(x, prec);
	}
	else
		y = BIG_NAN;

	return y;
}
