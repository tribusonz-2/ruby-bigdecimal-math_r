VALUE
LOG2_BBP2002(VALUE prec)
{
	const ID mult = rb_intern("mult");
	const ID div = rb_intern("div");
	VALUE two = rb_BigDecimal1(INT2FIX(2)),
	      nine = rb_BigDecimal1(INT2FIX(9)),
	      a = BIG_ONE,
	      r = BIG_ONE,
	      s = BIG_ZERO,
	      d = BIG_ONE,
	      n = rb_numdiff_make_n(prec), m;
	while (rb_numdiff_condition_p(s, d, n, &m))
	{
		d = rb_funcall(r, div, 2, a, m);
		s = rb_funcall1(s, '+', d);
		a = rb_funcall1(a, '+', two);
		r = rb_funcall(r, div, 2, nine, m);
	}
	s = rb_funcall(s, mult, 2,
		rb_Rational(INT2FIX(2), INT2FIX(3)), prec);
	RB_GC_GUARD(two);
	RB_GC_GUARD(nine);
	RB_GC_GUARD(d);
	RB_GC_GUARD(a);
	RB_GC_GUARD(r);
	RB_GC_GUARD(s);
	return s;
}
