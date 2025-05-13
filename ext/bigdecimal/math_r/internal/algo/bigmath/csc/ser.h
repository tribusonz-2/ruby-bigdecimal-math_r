VALUE
csc_ser(VALUE x, VALUE prec)
{
	VALUE sin;

	rb_check_precise(prec);

	rb_bigmath_sincos(x, prec, &sin, NULL);

	return rb_num_canonicalize(sin, prec, ARG_REAL, ARG_RECIPROCAL);
}
