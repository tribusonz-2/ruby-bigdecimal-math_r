VALUE
asec_branch(VALUE x, VALUE prec, bigmath_func1 asec_cb)
{
	const ID div = rb_intern("div");
	VALUE y = Qundef;
	VALUE p_domain = rb_range_new(INT2FIX(1), DBL2NUM(HUGE_VAL), false);
	VALUE m_domain = rb_range_new(DBL2NUM(-HUGE_VAL), INT2FIX(-1), true);

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (rb_num_nan_p(x))
		y = BIG_NAN;
	else if (rb_num_infinite_p(x) != 0)
		y = rb_funcall(rb_bigmath_const_pi(prec), div, 2, INT2FIX(2), prec);
	else if (rb_num_equal_p(x, INT2FIX(-1)))
		y = rb_bigmath_const_pi(prec);
	else if (rb_num_equal_p(x, INT2FIX(1)))
		y = BIG_ZERO;
	else if (rb_num_domain_p(p_domain, x) || rb_num_domain_p(m_domain, x))
		y = asec_cb(x, prec);
	else
		y = BIG_NAN;

	return y;
}
