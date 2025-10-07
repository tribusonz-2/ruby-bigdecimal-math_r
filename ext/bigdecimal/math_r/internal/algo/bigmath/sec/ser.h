VALUE
sec_ser(VALUE x, VALUE prec)
{
	VALUE sec, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	rb_bigmath_sincos(x, n, NULL, &sec);
	sec = rb_num_canonicalize(sec, n, ARG_REAL, ARG_RECIPROCAL);
	
	return rb_num_round(sec, prec);
}
