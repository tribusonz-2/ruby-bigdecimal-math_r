// Reference: C-gengo no yoru hyoujun algorithm jiten - Haruhiko Okumura
VALUE
hypot_mmm(VALUE a, VALUE b, VALUE prec)
{
	const ID div = rb_intern("div");
	const ID mult = rb_intern("mult");
	VALUE n = rb_numdiff_make_n(prec), m = Qundef;
        VALUE two = rb_BigDecimal1(INT2FIX(2));
	VALUE four = rb_BigDecimal1(INT2FIX(4));
	VALUE t = BIG_ONE;
	if (rb_num_negative_p(a))  a = rb_num_uminus(a);
	if (rb_num_negative_p(b))  b = rb_num_uminus(b);
	if (rb_num_coerce_cmp(a, b, '<'))
	{
		t = a; a = b; b = t;
	}
	if (rb_num_zero_p(b))  return a;
	while (rb_numdiff_condition_p(a, t, n, &m))
	{
		t = rb_funcall(b, div, 2, a, m);
		t = rb_funcall(t, mult, 2, t, m);
		t = rb_funcall1(t, '/', rb_funcall1(four, '+', t));
		a = rb_funcall1(a, '+', 
			rb_funcall1(rb_funcall1(two, '*', a), '*', t));
		b = rb_funcall1(b, '*', t);
	}
	return rb_num_round(a, prec);
}
