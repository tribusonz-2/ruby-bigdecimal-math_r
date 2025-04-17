VALUE
rb_bigmath_const_log10(VALUE prec)
{
	return rb_bigmath_const(BIGMATH_LOG10, LOG10_ser, prec);
}
