VALUE
erf_branch(VALUE x, VALUE prec, bigmath_func1 erf_cb)
{
	VALUE y = Qundef;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (!rb_num_finite_p(x))
	{
		if (rb_num_nan_p(x))
			y = BIG_NAN;
		else
			y = rb_num_negative_p(x) ? BIG_MINUS_ONE : BIG_ONE;
	}
	if (y == Qundef)
		y = erf_cb(x, prec);
	return y;
}
