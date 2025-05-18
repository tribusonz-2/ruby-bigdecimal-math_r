// Reference: C-gengo ni yoru hyoujun algorithm jiten - Haruhiko Okumura
VALUE
sqrt_newton(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE s = Qundef, t = Qundef, last = Qundef, n;
	VALUE two;

	rb_check_precise(prec);

	if (rb_num_zero_p(x))
		return BIG_ZERO;
	else if (rb_num_positive_p(x))
	{
		if (rb_num_infinite_p(x))
			return BIG_INF;
		n = rb_numdiff_make_n(prec);
		s = RTEST(rb_num_coerce_cmp(x, INT2FIX(1), '>')) ? x : BIG_ONE;
		two = rb_BigDecimal1(INT2FIX(2));
		do {
			last = s;
			t = rb_funcall1(x, '/', s);
			t = rb_funcall1(t, '+', s);
			s = rb_funcall(t, div, 2, two, n);
		} while (rb_num_coerce_cmp(s, last, '<'));

		RB_GC_GUARD(s);
		RB_GC_GUARD(t);
		RB_GC_GUARD(last);
		RB_GC_GUARD(two);

		return rb_num_round(last, prec);
	}
	else
		return BIG_NAN;
}
