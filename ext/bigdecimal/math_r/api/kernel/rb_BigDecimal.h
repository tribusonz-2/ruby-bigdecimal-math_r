VALUE
rb_BigDecimal(VALUE x, VALUE prec)
{
	const ID BigDecimal = rb_intern("BigDecimal");
	return rb_funcall(rb_cObject, BigDecimal, 2, x, prec);
}
