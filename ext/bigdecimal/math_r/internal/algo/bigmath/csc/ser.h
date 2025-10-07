VALUE
csc_ser(VALUE x, VALUE prec)
{
	VALUE sin, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	rb_bigmath_sincos(x, n, &sin, NULL);
	sin = rb_num_canonicalize(sin, n, ARG_REAL, ARG_RECIPROCAL);

	return rb_num_round(sin, prec);
}
