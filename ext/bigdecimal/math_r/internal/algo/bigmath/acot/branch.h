VALUE
acot_branch(VALUE x, VALUE prec, bigmath_func1 acot_cb)
{
	VALUE y;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (rb_num_nan_p(x))
		y = BIG_NAN;
	else if (rb_num_infinite_p(x) != 0)
		y = rb_num_negative_p(x) ? BIG_MINUS_ZERO : BIG_ZERO;
	else
		y = acot_cb(x, prec);

	return y;
}
