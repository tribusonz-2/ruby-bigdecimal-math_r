VALUE
atanh_branch(VALUE x, VALUE prec, bigmath_func1 atanh_cb)
{
	const ID leq = rb_intern("<=");
	VALUE y = Qundef;
	VALUE p0999 = rb_BigDecimal1(rb_str_new_cstr("0.999"));
	VALUE domain = rb_range_new(INT2FIX(-1), INT2FIX(1), true);

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (rb_num_domain_p(domain, x))
	{
		VALUE absx = rb_num_negative_p(x) ? rb_num_uminus(x) : x;
		if (rb_num_equal_p(absx, INT2FIX(1)))
			y = rb_num_negative_p(x) ? BIG_MINUS_INF : BIG_INF;
		else if (RTEST(rb_num_coerce_cmp(absx, p0999, leq)))
			y = atanh_ser(x, prec);
		else
			y = atanh_cb(x, prec);
	}
	else
		y = BIG_NAN;

	return y;
}
