VALUE
rb_big_minus_infinity(void)
{
	return rb_num_uminus(rb_big_infinity());
}
