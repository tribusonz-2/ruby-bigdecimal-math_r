VALUE
expxt_edf(VALUE x, VALUE t, VALUE prec)
{
	const ID mult = rb_intern("mult");
	const ID div = rb_intern("div");
	VALUE n, m, a, xt, e;
	long i = 0;

	rb_check_precise(prec);

	n = rb_numdiff_make_n(prec), m;
	a = BIG_ONE;
	xt = rb_funcall1(x, '*', t);
	e = BIG_ZERO;

	if (rb_num_zero_p(xt))
		return e;

	while (rb_numdiff_condition_p(e, a, n, &m))
	{
		e = rb_funcall1(e, '+', a);
		a = rb_funcall(a, div, 2, LONG2NUM(++i), m);
		a = rb_funcall(a, mult, 2, xt, m);
	}

	RB_GC_GUARD(a);
	RB_GC_GUARD(xt);
	RB_GC_GUARD(e);

	return rb_num_round(e, prec);
}
