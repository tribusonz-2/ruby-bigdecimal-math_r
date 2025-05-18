VALUE
erf_ser_inf(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	const ID mult = rb_intern("mult");
	VALUE n, m, s, zero, one, two, x2, f, r, i, i2, d, y;

	n = rb_numdiff_make_n(prec);

	s = rb_bigmath_exp(rb_funcall1(rb_num_uminus(x), '*', x), n);
	if (rb_num_zero_p(rb_num_round(s, prec)))
		return rb_num_negative_p(x) ? BIG_MINUS_ONE : BIG_ONE;
	s = rb_funcall(s, div, 2, rb_bigmath_sqrt(rb_bigmath_const_pi(n), n), n);

	zero = BIG_ZERO;
	one = BIG_ONE;
	two = rb_BigDecimal1(INT2FIX(2));

	x = rb_funcall1(two, '*', x);
	x2 = rb_funcall1(x, '*', x);
	f = one;
	r = one;
	i = zero;
	i2 = one;
	d = x;
	y = zero;

	while (rb_numdiff_condition_p(y, d, n, &m))
	{
		d = rb_funcall(rb_funcall1(f, '*', x), div, 2, r, m);
		y = rb_funcall1(y, '+', d);
		x = rb_funcall(x, mult, 2, x2, n);
		f = rb_funcall1(f, '*', i = rb_funcall1(i, '+', one));
		r = rb_funcall1(r, '*', rb_funcall1(
			i2 = rb_funcall1(i2, '+', one), '*', 
			i2 = rb_funcall1(i2, '+', one)));
	}

	RB_GC_GUARD(s);
	RB_GC_GUARD(zero);
	RB_GC_GUARD(one);
	RB_GC_GUARD(two);
	RB_GC_GUARD(x2);
	RB_GC_GUARD(x);
	RB_GC_GUARD(f);
	RB_GC_GUARD(r);
	RB_GC_GUARD(i);
	RB_GC_GUARD(i2);
	RB_GC_GUARD(d);
	RB_GC_GUARD(y);

	return rb_funcall(s, mult, 2, y, prec);
}
