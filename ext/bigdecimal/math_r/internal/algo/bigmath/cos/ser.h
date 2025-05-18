VALUE
cos_ser(VALUE x, VALUE prec)
{
	VALUE cos;

	rb_check_precise(prec);

	rb_bigmath_sincos(x, prec, NULL, &cos);
	cos = rb_num_round(cos, prec);

	return cos;
}
