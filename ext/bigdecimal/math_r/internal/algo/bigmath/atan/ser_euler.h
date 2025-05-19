VALUE
atan_ser_euler(VALUE x, VALUE prec)
{
	const ID add = rb_intern("add");
	const ID mult = rb_intern("mult");
	const ID div = rb_intern("div");
	const ID exponent = rb_intern("exponent");
	const ID double_fig = rb_intern("double_fig");
	VALUE m, y, w, t, s;
	long n = 1;

	if (rb_num_zero_p(x))
		return BIG_ZERO;

	m = rb_funcall1(rb_funcall(rb_cBigDecimal, double_fig, 0), '+', prec);
	y = rb_funcall(
		rb_funcall(x, mult, 2, x, m), div, 2,
		rb_funcall(BIG_ONE, add, 2, rb_funcall(x, mult, 2, x, m),
		m), m);
	w = BIG_ONE;
	t = BIG_ONE;
	s = BIG_ZERO;

	for ( ; ; )
	{
		VALUE a = rb_funcall(t, mult, 2, w, m);

		if (rb_num_negative_p(rb_funcall1(m, '+', rb_funcall(a, exponent, 0))))
			break;
		s = rb_funcall(s, add, 2, a, m);
		t = rb_funcall(t, mult, 2, LONG2NUM(++n), m);
		t = rb_funcall(t, div, 2, LONG2NUM(++n), m);
		w = rb_funcall(w, mult, 2, y, m);
	};
	return rb_funcall(rb_funcall(y, div, 2, x, prec), mult, 2, s, prec);
}
