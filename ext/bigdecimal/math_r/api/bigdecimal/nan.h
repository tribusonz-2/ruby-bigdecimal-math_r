VALUE
rb_big_nan(void)
{
	const ID _NAN = rb_intern("NAN");
	return rb_const_get_at(rb_cBigDecimal, _NAN);
}
