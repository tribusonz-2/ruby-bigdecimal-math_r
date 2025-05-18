VALUE
asin_branch(VALUE x, VALUE prec, bigmath_func1 asin_cb)
{
	const ID leq = rb_intern("<=");
	VALUE y = Qundef, p001 = rb_BigDecimal1(rb_str_new_cstr("0.001"));

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (!rb_num_finite_p(x))
		y = x;
	else
	{
		VALUE absx = rb_num_negative_p(x) ? rb_num_uminus(x) : x;
		if (RTEST(rb_num_coerce_cmp(absx, p001, leq)))
			y = asin_ser(x, prec);
		else if (RTEST(rb_num_coerce_cmp(absx, BIG_ONE, leq)))
			y = asin_cb(x, prec);
		else
			y = BIG_NAN;
	}
	return y;
}
