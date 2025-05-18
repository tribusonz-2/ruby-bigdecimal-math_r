VALUE
log_ser_okumura(VALUE x, VALUE prec)
{
	const ID add = rb_intern("add");
	const ID div = rb_intern("div");
	const ID mult = rb_intern("mult");
	const ID pow = rb_intern("**");
	const ID succ = rb_intern("succ");
	bool inv;
	VALUE one = BIG_ONE;
	VALUE two = rb_BigDecimal1(INT2FIX(2));
	VALUE n = rb_numdiff_make_n(prec), m;
	VALUE k, x2, i, s, d, y;
	
	inv = RTEST(rb_num_coerce_cmp(x, INT2FIX(1), '>'));
	if (inv)
		x = rb_num_canonicalize(x, n, ARG_REAL, ARG_RECIPROCAL);
	else
		x = rb_num_canonicalize(x, n, ARG_REAL, ARG_RAWVALUE);
	
	rcm2_edf(rb_funcall1(x, '/', rb_bigmath_const_sqrt2(n)), &k);
	k = rb_funcall(k, succ, 0);
	k = rb_BigDecimal1(k);
	x = rb_funcall1(x, '/', rb_funcall1(two, pow, k));
	x = rb_funcall(
		rb_funcall1(x, '-', one), div, 2,
		rb_funcall1(x, '+', one), n);
#if 0
	x2 = rb_funcall1(x, '*', x);
#else
	x2 = rb_funcall(x, mult, 2, x, n);
#endif
	i = one;
	s = x;
	d = one;
	while (rb_numdiff_condition_p(s, d, n, &m))
	{
		x = rb_funcall(x, mult, 2, x2, m);
		i = rb_funcall1(i, '+', two);
		d = rb_funcall(x, div, 2, i, m);
		s = rb_funcall1(s, '+', d);
	}

	y = rb_funcall(
		rb_funcall1(rb_bigmath_const_log2(n), '*', k),
		add, 2, rb_funcall1(two, '*', s), prec);

	RB_GC_GUARD(x);
	RB_GC_GUARD(x2);
	RB_GC_GUARD(i);
	RB_GC_GUARD(s);
	RB_GC_GUARD(d);
	RB_GC_GUARD(one);
	RB_GC_GUARD(two);

	return inv ? rb_num_uminus(y) : y;
}
