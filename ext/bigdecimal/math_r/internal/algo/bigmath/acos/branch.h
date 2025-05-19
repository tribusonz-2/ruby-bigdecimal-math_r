VALUE
acos_branch(VALUE x, VALUE prec, bigmath_func1 acos_cb)
{
	const ID leq = rb_intern("<=");
	VALUE y = Qundef;
	VALUE p001 = rb_BigDecimal1(rb_str_new_cstr("0.001"));
	VALUE domain = rb_range_new(INT2FIX(0), INT2FIX(1), false);

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (!rb_num_finite_p(x))
		y = x;
	else
	{
		VALUE absx = rb_num_abs(x);
		if (RTEST(rb_num_coerce_cmp(absx, p001, leq)))
		{
			y = acos_ser(x, prec);
		}
		else if (rb_num_domain_p(domain, absx))
		{
			if (rb_num_equal_p(absx, INT2FIX(1)))
				y = rb_num_negative_p(x) ? 
					rb_bigmath_const_pi(prec) : BIG_ZERO;
			else
				y = acos_cb(x, prec);
		}
		else
			y = BIG_NAN;
	}
	return y;
}
