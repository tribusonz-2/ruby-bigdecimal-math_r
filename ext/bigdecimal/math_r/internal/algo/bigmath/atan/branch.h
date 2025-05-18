VALUE
atan_branch(VALUE x, VALUE prec, bigmath_func1 atan_cb)
{
	VALUE y = Qundef;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (rb_num_nan_p(x))
		y = BIG_NAN;
	if (rb_num_zero_p(x))
		y = BIG_ZERO;
	else
		y = atan_cb(x, prec);

	return y;
}
