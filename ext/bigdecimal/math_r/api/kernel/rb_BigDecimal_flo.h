VALUE
rb_BigDecimal_flo(VALUE x)
{
	const ID BigDecimal = rb_intern("BigDecimal");
	const ID DIG = rb_intern("DIG");
	VALUE FLOAT_DIG = rb_const_get_at(rb_cFloat, DIG);
	VALUE y = rb_funcall(rb_cObject, BigDecimal, 2, x, FLOAT_DIG);
	return y;
}
