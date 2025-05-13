VALUE
log1p_p_adic(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE n, m, zero, one, t, i, d, y, c;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	zero = BIG_ZERO;
	one = BIG_ONE;

	t = x;
	i = one;
	d = one;
	y = zero;
	c = one;

	while (rb_numdiff_condition_p(y, d, n, &m))
	{
		d = rb_funcall( rb_funcall1(c, '*', t), div, 2, i, m);
		y = rb_funcall1(y, '+', d);
		c = rb_num_uminus(c);
		i = rb_funcall1(i, '+', one);
		t = rb_funcall1(t, '*', x);
	}

	RB_GC_GUARD(zero);
	RB_GC_GUARD(one);
	RB_GC_GUARD(t);
	RB_GC_GUARD(i);
	RB_GC_GUARD(d);
	RB_GC_GUARD(y);
	RB_GC_GUARD(c);

	return rb_num_round(y, prec);
}
