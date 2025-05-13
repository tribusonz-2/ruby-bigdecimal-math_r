VALUE
sec_ser(VALUE x, VALUE prec)
{
	VALUE cos;

	rb_check_precise(prec);

	rb_bigmath_sincos(x, prec, NULL, &cos);

	return rb_num_canonicalize(cos, prec, ARG_REAL, ARG_RECIPROCAL);
}
