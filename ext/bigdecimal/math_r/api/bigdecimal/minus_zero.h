VALUE
rb_big_minus_zero(void)
{
	VALUE y = rb_BigDecimal1(rb_str_new_cstr("-0"));
	return y;
}
