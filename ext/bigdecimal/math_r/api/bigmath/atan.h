
VALUE
rb_bigmath_atan(VALUE x, VALUE prec)
{
	atan_cb = atan_ser_euler;
	return atan_branch(x, prec);
}
