VALUE
expxt_edf(VALUE x, VALUE t, VALUE prec)
{
	const ID add = rb_intern("add");
	const ID mult = rb_intern("mult");
	const ID div = rb_intern("div");
	VALUE n = rb_numdiff_make_n(prec), m;
	VALUE a = BIG_ONE;
	VALUE xt = rb_funcall1(x, '*', t);
	VALUE e = BIG_ZERO;
	long i = 0;
	if (rb_num_zero_p(xt))
		return e;
	while (rb_numdiff_condition_p(e, a, n, &m))
	{
		e = rb_funcall(e, add, 2, a, m);
		a = rb_funcall(a, div, 2, LONG2NUM(++i), m);
		a = rb_funcall(a, mult, 2, xt, m);
	}
	return rb_num_round(e, prec);
}
