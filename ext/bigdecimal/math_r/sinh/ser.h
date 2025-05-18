VALUE
sinh_ser(VALUE x, VALUE prec)
{
	VALUE y = Qundef;

	rb_check_precise(prec);

	sinhcosh_ser(x, prec, &y, NULL);

	return y;
}
