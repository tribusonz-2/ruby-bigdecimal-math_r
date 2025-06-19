VALUE
cexpm1_branch(VALUE z, VALUE prec, bigmath_func1 cexpm1_cb)
{
	VALUE w = Qundef;

	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);

	if (rb_num_nan_p(z))
		w = rb_Complex(BIG_NAN, BIG_NAN);
	else
		w = cexpm1_cb(z, prec);
	return w;
}
