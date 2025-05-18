VALUE
rb_BigDecimal1(VALUE x)
{
	const ID BigDecimal = rb_intern("BigDecimal");
	return rb_funcall(rb_cObject, BigDecimal, 1, x);
}
