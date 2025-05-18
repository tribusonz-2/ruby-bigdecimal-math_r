void
sincos_ser(VALUE x, VALUE prec, VALUE *sin, VALUE *cos)
{
	const ID div = rb_intern("div");
	VALUE n, m, f, w, a, y;
	long i = 0;
	
	if (sin == NULL && cos == NULL)
		return;
	
	if (!rb_num_finite_p(x))
	{
		if (sin != NULL)  *sin = BIG_NAN;
		if (cos != NULL)  *cos = BIG_NAN;
		return;
	}
	n = rb_numdiff_make_n(prec);
	f = BIG_ONE;
	w = BIG_ONE;
	a = BIG_ONE;
	y = BIG_ZERO;
	if (sin != NULL)  *sin = BIG_ZERO;
	if (cos != NULL)  *cos = BIG_ZERO;
	while (rb_numdiff_condition_p(y, a, n, &m))
	{
		a = rb_funcall(w, div, 2, f, m);
		switch (i % 4) {
		case 0:
			if (cos != NULL) *cos = (y = rb_funcall1(*cos, '+', a));
			break;
		case 1:
			if (sin != NULL) *sin = (y = rb_funcall1(*sin, '+', a));
			break;
		case 2:
                        if (cos != NULL) *cos = (y = rb_funcall1(*cos, '-', a));
			break;
		case 3:
                        if (sin != NULL) *sin = (y = rb_funcall1(*sin, '-', a));
			break;
		}
		w = rb_funcall1(w, '*', x);
		f = rb_funcall1(f, '*', LONG2NUM(++i));
	}
	RB_GC_GUARD(f);
	RB_GC_GUARD(w);
	RB_GC_GUARD(a);
	RB_GC_GUARD(y);
	if (sin != NULL)  RB_GC_GUARD(*sin);
	if (cos != NULL)  RB_GC_GUARD(*cos);
}
