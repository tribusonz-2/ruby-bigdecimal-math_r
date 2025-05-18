VALUE
cot_ser(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE sin, cos;

	rb_check_precise(prec);

	rb_bigmath_sincos(x, prec, &sin, &cos);

	return rb_funcall(cos, div, 2, sin, prec);
}
