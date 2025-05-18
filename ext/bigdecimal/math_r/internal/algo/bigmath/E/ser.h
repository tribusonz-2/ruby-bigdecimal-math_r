VALUE
E_ser(VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE n, m, a, e;
	long k = 0; // TODO: should be break when number is exceeded to LONG_MAX?

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	a = BIG_ONE;
	e = BIG_ZERO;

	while (rb_numdiff_condition_p(e, a, n, &m))
	{
		e = rb_funcall1(e, '+', a);
		a = rb_funcall(a, div, 2, LONG2NUM(++k), m);
	}
	RB_GC_GUARD(a);
	RB_GC_GUARD(e);
        return rb_num_round(e, prec);
}
