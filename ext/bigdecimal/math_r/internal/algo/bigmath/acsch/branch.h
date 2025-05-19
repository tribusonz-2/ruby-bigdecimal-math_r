VALUE
acsch_branch(VALUE x, VALUE prec, bigmath_func1 acsch_cb)
{
	VALUE y = Qundef;
	int sign;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (rb_num_nan_p(x))
		y = BIG_NAN;
	else if ((sign = rb_num_infinite_p(x)) != 0)
		y = sign == 1 ? BIG_ZERO : BIG_MINUS_ZERO;
	else if (rb_num_zero_p(x))
		y = BIG_INF;
	else 
		y = acsch_cb(x, prec);

	return y;
}
