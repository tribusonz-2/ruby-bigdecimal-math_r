VALUE
tan_ser(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE sin, cos, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	rb_bigmath_sincos(x, n, &sin, &cos);

	return rb_funcall(sin, div, 2, cos, prec);
}
