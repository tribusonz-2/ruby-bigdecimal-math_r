VALUE
atanh_ser(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	const ID mult = rb_intern("mult");
	VALUE one, two, i, d, y, x2, n, m;

	n = rb_numdiff_make_n(prec);

	one = BIG_ONE;
	two = rb_BigDecimal1(INT2FIX(2));
	i = one;
	x2 = rb_funcall1(x, '*', x);
	d = one;
	y = BIG_ZERO;

	while (rb_numdiff_condition_p(y, d, n, &m))
	{
		d = rb_funcall(x, div, 2, i, m);
		y = rb_funcall1(y, '+', d);
		x = rb_funcall(x, mult, 2, x2, m);
		i = rb_funcall1(i, '+', two);
	}

	RB_GC_GUARD(one);
	RB_GC_GUARD(two);
	RB_GC_GUARD(i);
	RB_GC_GUARD(d);
	RB_GC_GUARD(y);
	RB_GC_GUARD(x2);

	return rb_num_round(y, prec);
}
