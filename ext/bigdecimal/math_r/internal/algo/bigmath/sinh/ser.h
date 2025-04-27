VALUE
sinh_ser(VALUE x, VALUE prec)
{
	VALUE y = Qundef;
	sinhcosh_ser(x, prec, &y, NULL);
	return y;
}
