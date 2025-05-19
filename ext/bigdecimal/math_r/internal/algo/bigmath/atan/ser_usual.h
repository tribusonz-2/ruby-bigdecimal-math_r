VALUE
atan_ser_usual(VALUE x, VALUE prec)
{
	const ID mult = rb_intern("mult");
	const ID div = rb_intern("div");
	VALUE y, d, r, t, x2, n, m, two;

	rb_check_precise(prec);

	two = rb_BigDecimal1(INT2FIX(2));
	n = rb_numdiff_make_n(prec);
	y = x;
	d = y;
	t = x;
	r = rb_BigDecimal1(INT2FIX(3));
	x2 = rb_funcall(x, mult, 2, x, n);

	while (rb_numdiff_condition_p(y, d, n, &m))
	{
		t = rb_funcall(rb_num_uminus(t), mult, 2, x2, n);
		d = rb_funcall(t, div, 2, r, m);
		y = rb_funcall1(y, '+', d);
		r = rb_funcall1(r, '+', two);
	}

	RB_GC_GUARD(y);
	RB_GC_GUARD(d);
	RB_GC_GUARD(r);
	RB_GC_GUARD(t);
	RB_GC_GUARD(x2);
	RB_GC_GUARD(two);

	return y;
}
