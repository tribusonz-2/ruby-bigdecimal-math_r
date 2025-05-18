VALUE
erf_cf(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE n, zero, one, two, c, b, p1, q1, p2, q2, i, prev, t;

	n = rb_numdiff_make_n(prec);

	zero = BIG_ZERO;
	one = BIG_ONE;
	two = rb_BigDecimal1(INT2FIX(2));

	c = rb_num_uminus(rb_bigmath_exp(rb_funcall1(rb_num_uminus(x), '*', x), n));
	if (rb_num_zero_p(rb_num_round(c, prec)))
		return rb_num_negative_p(x) ? BIG_MINUS_ONE : BIG_ONE;
	c = rb_funcall1(c, '/', rb_bigmath_sqrt(rb_bigmath_const_pi(n), n));
	b = x;

	p1 = one;  q1 = zero;  p2 = one;  q2 = one;
	i = one;
	do {
		prev = p2;
		t = rb_funcall1(rb_funcall1(p1, '*', c), '+', rb_funcall1(p2, '*', b));  p1 = p2;  p2 = t;
                t = rb_funcall1(rb_funcall1(q1, '*', c), '+', rb_funcall1(q2, '*', b));  q1 = q2;  q2 = t;
		if (rb_num_nonzero_p(q2))
		{
			p1 = rb_funcall(p1, div, 2, q2, n);  q1 = rb_funcall(q1, div, 2, q2, n);
			p2 = rb_funcall(p2, div, 2, q2, n);  q2 = one;
		}
		i = rb_funcall1(i, '+', one);
		c = rb_funcall1(i, '-', one);
		b = rb_num_equal_p(rb_funcall1(i, '%', two), one) ? x : rb_funcall1(two, '*', x);
	} while (rb_num_nonzero_p(q2) && rb_num_notequal_p(prev, p2));
	if (rb_num_negative_p(x))
		p2 = rb_num_uminus(p2);

	RB_GC_GUARD(zero);
	RB_GC_GUARD(one);
	RB_GC_GUARD(two);
	RB_GC_GUARD(c);
	RB_GC_GUARD(b);
	RB_GC_GUARD(p1);
	RB_GC_GUARD(q1);
	RB_GC_GUARD(p2);
	RB_GC_GUARD(q2);
	RB_GC_GUARD(i);
	RB_GC_GUARD(prev);
	RB_GC_GUARD(t);

	return rb_num_round(p2, prec);
}
