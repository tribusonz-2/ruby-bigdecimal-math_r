VALUE
expm1_branch(VALUE x, VALUE prec, bigmath_func1 expm1_cb)
{
	VALUE w = Qundef;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (rb_num_nan_p(x))
		w = BIG_NAN;
	else
		w = expm1_cb(x, prec);
	return w;
}
