VALUE
rb_BigDecimal_flo(VALUE x)
{
	const ID BigDecimal = rb_intern("BigDecimal");
	const ID DIG = rb_intern("DIG");
	VALUE FLOAT_DIG, y;
	if (rb_num_nan_p(x))
		y = BIG_NAN;
	else
	{
		FLOAT_DIG = rb_const_get_at(rb_cFloat, DIG);
		y = rb_funcall(rb_cObject, BigDecimal, 2, x, FLOAT_DIG);
	}
	return y;
}
