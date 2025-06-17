VALUE
cuberoot_branch(VALUE x, VALUE prec, bigmath_func1 cuberoot_cb)
{
	bool positive;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (!rb_num_finite_p(x) || rb_num_zero_p(x))
		return x;
	positive = rb_num_positive_p(x) ? true : false;

	if (!positive)
		x = rb_num_uminus(x);

	x = cuberoot_cb(x, prec);

	return positive ? x : rb_num_uminus(x);
}
