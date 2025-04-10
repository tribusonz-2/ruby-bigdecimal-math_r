VALUE
sec_ser(VALUE x, VALUE prec)
{
	VALUE cos;
	rb_check_precise(prec);
	if (!rb_num_finite_p(x))
		return BIG_NAN;
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	rb_bigmath_sincos(x, prec, NULL, &cos);
	return rb_num_canonicalize(cos, prec, ARG_REAL, ARG_RECIPROCAL);
}
