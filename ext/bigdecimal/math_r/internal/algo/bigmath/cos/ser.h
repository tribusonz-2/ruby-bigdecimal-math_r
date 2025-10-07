VALUE
cos_ser(VALUE x, VALUE prec)
{
	VALUE cos, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	rb_bigmath_sincos(x, n, NULL, &cos);

	return rb_num_round(cos, prec);
}
