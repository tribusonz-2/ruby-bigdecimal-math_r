
VALUE
PI_machin(VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE m, n, one, two, m25, m57121, pi, k, t, d;
	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);
	one = BIG_ONE;
	two = rb_BigDecimal1(INT2FIX(2));
	m25 = rb_BigDecimal1(rb_str_new_cstr("-0.04"));
	m57121 = rb_BigDecimal1(rb_str_new_cstr("-57121"));
	pi = BIG_ZERO;
	k = BIG_ONE;
	t = rb_BigDecimal(rb_Rational(INT2FIX(16), INT2FIX(5)), n);
	d = one;
	while (rb_numdiff_condition_p(pi, d, n, &m))
	{
		d = rb_funcall(t, div, 2, k, m);
		pi = rb_funcall1(pi, '+', d);
		t = rb_funcall1(t, '*', m25);
		k = rb_funcall1(k, '+', two);
	}
	k = BIG_ONE;
	t = rb_BigDecimal(rb_Rational(INT2FIX(4), INT2FIX(239)), n);
	d = one;
	while (rb_numdiff_condition_p(pi, d, n, &m))
	{
		d = rb_funcall(t, div, 2, k, m);
		pi = rb_funcall1(pi, '-', d);
		t = rb_funcall(t, div, 2, m57121, n);
		k = rb_funcall1(k, '+', two);
	}
	RB_GC_GUARD(one);
	RB_GC_GUARD(two);
	RB_GC_GUARD(m25);
	RB_GC_GUARD(m57121);
	RB_GC_GUARD(pi);
	RB_GC_GUARD(k);
	RB_GC_GUARD(t);
	RB_GC_GUARD(d);
	return rb_num_round(pi, prec);
}
