VALUE
EulerGamma_borwein_bailey(VALUE prec)
{
	const ID add = rb_intern("add");
	const ID div = rb_intern("div");
	VALUE zero, one, m, n, nn, a, b, u, v, k;
	rb_check_precise(prec);
	zero = BIG_ZERO;
	one = BIG_ONE;
	n = rb_numdiff_make_n(prec);
	nn = rb_BigDecimal1(n);
	a = u = rb_num_uminus(rb_bigmath_log(n, n));
	b = v = one;
	k = zero;
	while (rb_numdiff_condition_p(u, a, n, &m))
	{
		k = rb_funcall1(k, '+', one);
		b = rb_funcall(rb_funcall1(b, '*', rb_funcall1(nn, '*', nn)), 
			div, 2, rb_funcall1(k, '*', k), m);
		a = rb_funcall1(
			rb_funcall(one, div, 2, k, m), '*', 
			rb_funcall(rb_funcall(rb_funcall1(a, '*', rb_funcall1(nn, '*', nn)), 
			div, 2, k, m),
			add, 2, b, m));
		u = rb_funcall1(u, '+', a);
		v = rb_funcall1(v, '+', b);
	}
	RB_GC_GUARD(zero);
	RB_GC_GUARD(one);
	RB_GC_GUARD(nn);
	RB_GC_GUARD(a);
	RB_GC_GUARD(b);
	RB_GC_GUARD(u);
	RB_GC_GUARD(v);
	RB_GC_GUARD(k);
	return rb_funcall(u, div, 2, v, prec);
}
