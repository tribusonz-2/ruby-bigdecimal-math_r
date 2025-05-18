VALUE
sin_ser(VALUE x, VALUE prec)
{
	VALUE sin;

	rb_check_precise(prec);

	rb_bigmath_sincos(x, prec, &sin, NULL);

	sin = rb_num_round(sin, prec);

	return sin;
}
