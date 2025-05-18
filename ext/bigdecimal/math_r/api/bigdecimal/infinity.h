VALUE
rb_big_infinity(void)
{
	const ID _INFINITY = rb_intern("INFINITY");
	return rb_const_get_at(rb_cBigDecimal, _INFINITY);
}
