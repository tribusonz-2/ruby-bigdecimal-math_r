VALUE
asinh_ser(VALUE x, VALUE prec)
{
	const ID mult = rb_intern("mult");
	VALUE n, m;
	VALUE one, two, x2, c, t, f_n, f_m, d, y, i;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	one = BIG_ONE;
	two = rb_BigDecimal1(INT2FIX(2));
	x2 = rb_funcall1(x, '*', x);
	y = BIG_ZERO;
	i = BIG_ZERO;
	c = one;
	t = one;
	f_n = one;
	f_m = one;
	d = one;

	while (rb_numdiff_condition_p(y, d, n, &m))
	{
		d = rb_funcall1(
			rb_funcall1(c, '*', f_n), '/', 
			rb_funcall1(t, '*', f_m));
		d = rb_funcall(d, mult, 2, x, m);
		y = rb_funcall1(y, '+', d);
		c = rb_num_uminus(c);
		t = rb_funcall1(t, '+', two);
		i = rb_funcall1(i, '+', one);
		f_n = rb_funcall1(f_n, '*', i);
		i = rb_funcall1(i, '+', one);
		f_m = rb_funcall1(f_m, '*', i);
		x = rb_funcall(x, mult, 2, x2, m);
	}

	RB_GC_GUARD(one);
	RB_GC_GUARD(two);
	RB_GC_GUARD(x2);
	RB_GC_GUARD(c);
	RB_GC_GUARD(t);
	RB_GC_GUARD(f_n);
	RB_GC_GUARD(f_m);
	RB_GC_GUARD(y);
	RB_GC_GUARD(i);

	return rb_num_round(y, prec);
}
