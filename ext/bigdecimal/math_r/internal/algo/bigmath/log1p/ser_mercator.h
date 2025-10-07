VALUE
log1p_ser_mercator(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	const ID mult = rb_intern("mult");
	VALUE n;
	VALUE one;
	VALUE w;
	VALUE t;
	VALUE d;
	VALUE y;
	int sign = 1;
	VALUE m = Qundef;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	one = BIG_ONE;
	t = one;
	d = BIG_ONE;
	y = BIG_ZERO;

	w = rb_num_canonicalize(x, n, ARG_REAL, ARG_RAWVALUE);

	while (rb_numdiff_condition_p(y, d, n, &m))
	{
		d = rb_funcall(w, div, 2, t, m);
		t = rb_funcall1(t, '+', one);
		w = rb_funcall(w, mult, 2, x, n);
		if (sign == 1)
			y = rb_funcall1(y, '+', d);
		else
			y = rb_funcall1(y, '-', d);
		sign *= -1;
	}

	RB_GC_GUARD(one);
	RB_GC_GUARD(w);
	RB_GC_GUARD(t);
	RB_GC_GUARD(d);
	RB_GC_GUARD(x);
	RB_GC_GUARD(y);

	return rb_num_round(y, prec);
}
