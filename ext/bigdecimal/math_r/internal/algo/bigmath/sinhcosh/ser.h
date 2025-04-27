static void
sinhcosh_inline(VALUE x, VALUE prec, VALUE *sinh, VALUE *cosh)
{
	const ID div = rb_intern("div");
	VALUE n, m, f, w, a, y;
	long i = 0;

	n = rb_numdiff_make_n(prec);
	f = BIG_ONE;
	w = BIG_ONE;
	a = BIG_ONE;
	y = BIG_ZERO;
	
	if (sinh == NULL && cosh == NULL)  return;
	
	if (sinh != NULL)  *sinh = BIG_ZERO;
	if (cosh != NULL)  *cosh = BIG_ZERO;
	while (rb_numdiff_condition_p(y, a, n, &m))
	{
		a = rb_funcall(w, div, 2, f, m);
		switch (i % 2) {
		case 0:
			if (cosh != NULL)  *cosh = (y = rb_funcall1(*cosh, '+', a));
			break;
		case 1:
                        if (sinh != NULL)  *sinh = (y = rb_funcall1(*sinh, '+', a));
 			break;
		}
		w = rb_funcall1(w, '*', x);
		f = rb_funcall1(f, '*', LONG2NUM(++i));
	}
	RB_GC_GUARD(f);
	RB_GC_GUARD(w);
	RB_GC_GUARD(a);
	RB_GC_GUARD(y);
	if (sinh != NULL)  RB_GC_GUARD(*sinh);
	if (cosh != NULL)  RB_GC_GUARD(*cosh);
}

void
sinhcosh_ser(VALUE x, VALUE prec, VALUE *sinh, VALUE *cosh)
{
	int sign;
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	if (rb_num_nan_p(x))
	{
		if (sinh != NULL)  *sinh = BIG_NAN;
		if (cosh != NULL)  *cosh = BIG_NAN;
	}
	else if ((sign = rb_num_infinite_p(x)) != 0)
	{
		switch (sign) {
		case 1:
			if (sinh != NULL)  *sinh = BIG_INF;
			if (cosh != NULL)  *cosh = BIG_INF;
			break;
		case -1:
			if (sinh != NULL)  *sinh = BIG_MINUS_INF;
			if (cosh != NULL)  *cosh = BIG_INF;
			break;
		}
	}
	else
	{
		sinhcosh_inline(x, prec, sinh, cosh);
		if (sinh != NULL)  *sinh = rb_num_round(*sinh, prec);
		if (cosh != NULL)  *cosh = rb_num_round(*cosh, prec);
	}
}
