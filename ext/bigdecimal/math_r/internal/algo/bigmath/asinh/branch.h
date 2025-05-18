VALUE
asinh_branch(VALUE x, VALUE prec, bigmath_func1 asinh_cb)
{
	VALUE y = Qundef, eps5 = rb_BigDecimal1(rb_str_new_cstr("0.001"));
	int sign;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (rb_num_nan_p(x))
		y = BIG_NAN;
	else if ((sign = rb_num_infinite_p(x)) != 0)
	{
		y = sign == 1 ? BIG_INF : BIG_MINUS_INF;
	}
	else if (rb_num_zero_p(x))
		y = BIG_ZERO;
	else
	{
		VALUE absx = rb_num_negative_p(x) ? rb_num_uminus(x) : x;
		if (RTEST(rb_num_coerce_cmp(absx, eps5, '<')))
			y = asinh_ser(x, prec);
		else
			y = asinh_cb(x, prec);
	 }
	return y;
}
