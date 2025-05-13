VALUE
cacsch_branch(VALUE z, VALUE prec, bigmath_func1 cacsch_cb)
{
	VALUE w = Qundef;

	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);

	if (rb_num_nan_p(z))
		w = rb_Complex(BIG_NAN, BIG_NAN);
	else if (rb_num_infinite_p(z) != 0)
		w = rb_Complex(BIG_ZERO, BIG_ZERO);
	else if (rb_num_zero_p(z))
		w = rb_Complex(BIG_INF, BIG_INF);
	else
		w = cacsch_cb(z, prec);

	return w;
}
