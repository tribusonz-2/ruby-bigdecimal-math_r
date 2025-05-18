VALUE
rb_bigmath_const_log2(VALUE prec)
{
	return rb_bigmath_const(BIGMATH_LOG2, LOG2_BBP2002, prec);
}
