VALUE
tanh_ser(VALUE x, VALUE prec)
{
	VALUE y = Qundef, sinh = Qundef, cosh = Qundef;
	const ID div = rb_intern("div");
	sinhcosh_ser(x, prec, &sinh, &cosh);
	y = rb_funcall(sinh, div, 2, cosh, prec);
	return y;
}
