VALUE
asin_ser(VALUE x, VALUE prec)
{
	const ID mult = rb_intern("mult");
	VALUE one, i, d, x2, y, n, m;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	one = BIG_ONE;
	i = BIG_ZERO;
	d = x;
	x2 = rb_funcall1(x, '*', x);
	y = BIG_ZERO;
	
	while (rb_numdiff_condition_p(y, d, n, &m))
	{
		y = rb_funcall1(y, '+', d);
		d = rb_funcall1(d, '*', i = rb_funcall1(i, '+', one));
		d = rb_funcall1(d, '/', i = rb_funcall1(i, '+', one));
		d = rb_funcall1(d, '*',     rb_funcall1(i, '+', one));
		d = rb_funcall(d, mult, 2, x2, m);
	}

	RB_GC_GUARD(one);
	RB_GC_GUARD(x);
	RB_GC_GUARD(x2);
	RB_GC_GUARD(i);
	RB_GC_GUARD(d);
	RB_GC_GUARD(y);

	return rb_num_round(y, prec);
}
