VALUE
cosh_ser(VALUE x, VALUE prec)
{
	VALUE y = Qundef;
	sinhcosh_ser(x, prec, NULL, &y);
	return y;
}
