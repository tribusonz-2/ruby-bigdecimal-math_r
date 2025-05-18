void
rb_bigmath_sincos(VALUE x, VALUE prec, VALUE *sin, VALUE *cos)
{
	sincos_ser(x, prec, sin, cos);
}
