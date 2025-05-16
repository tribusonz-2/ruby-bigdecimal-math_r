VALUE
erf_ser_zero(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	const ID mult = rb_intern("mult");
	VALUE n, m, zero, one, two, x2, f, r, i, d, y;

	n = rb_numdiff_make_n(prec);

	zero = BIG_ZERO;
	one = BIG_ONE;
	two = rb_BigDecimal1(INT2FIX(2));

	x2 = rb_funcall1(x, '*', x);
	f = one;
	r = one;
	i = one;
	d = x;
	y = zero;

	while (rb_numdiff_condition_p(y, d, n, &m))
	{
		d = rb_funcall(x, div, 2, rb_funcall1(f, '*', r), m);
		y = rb_funcall1(y, '+', d);
		x = rb_num_uminus(rb_funcall(x, mult, 2, x2, n));
		f = rb_funcall1(f, '*', i);
		r = rb_funcall1(r, '+', two);
		i = rb_funcall1(i, '+', one);
	}

	RB_GC_GUARD(zero);
	RB_GC_GUARD(one);
	RB_GC_GUARD(two);
	RB_GC_GUARD(x2);
	RB_GC_GUARD(x);
	RB_GC_GUARD(f);
	RB_GC_GUARD(r);
	RB_GC_GUARD(i);
	RB_GC_GUARD(d);
	RB_GC_GUARD(y);

	return rb_funcall(
		rb_funcall1(INT2FIX(2), '/', rb_bigmath_sqrt(rb_bigmath_const_pi(n), n)),
		mult, 2, y, prec);
}
