VALUE
coth_ser(VALUE x, VALUE prec)
{
	VALUE y = Qundef, sinh = Qundef, cosh = Qundef, n;
	const ID div = rb_intern("div");

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	sinhcosh_ser(x, n, &sinh, &cosh);
	y = rb_funcall(cosh, div, 2, sinh, prec);

	return y;
}
