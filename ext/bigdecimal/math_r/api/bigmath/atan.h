static VALUE
atan_euler_ser(VALUE x, VALUE prec)
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


VALUE
rb_bigmath_atan_cb(VALUE x, VALUE prec, bigmath_func1 atan_func)
{
	const ID add = rb_intern("add");
	const ID sub = rb_intern("sub");
	const ID div = rb_intern("div");
	const ID round = rb_intern("round");
	const ID sqrt = rb_intern("sqrt");
	bool neg, dbl, inv;
	VALUE pi;
	if (!atan_func)
		atan_func = atan_euler_ser;
	rb_check_precise(prec);
	if (rb_num_notequal_p(x, x))
		return BIG_NAN;
	if (rb_num_zero_p(x))
		return rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	pi = rb_bigmath_const_pi(prec);
	neg = rb_num_negative_p(x);
	if (neg)
		x = rb_num_uminus(x);
	if (rb_num_infinite_p(x) != 0)
		return rb_funcall(pi, div, 2,
			neg ? INT2NUM(-2) : INT2NUM(2), prec);
	if (rb_num_equal_p(rb_funcall(x, round, 1, prec), INT2FIX(1)))
		return rb_funcall(pi, div, 2,
			neg ? INT2NUM(-4) : INT2NUM(4), prec);
	inv = RTEST(rb_num_coerce_cmp(x, INT2FIX(1), '>'));
	if (inv)
		x = rb_funcall(BIG_ONE, div, 2, x, prec);
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	dbl = RTEST(rb_num_coerce_cmp(x, DBL2NUM(0.5), '>'));
	if (dbl)
		// x = (-1 + sqrt(1 + x**2, prec))/x
		x = rb_funcall1(
			rb_funcall1(INT2FIX(-1), '+', 
			rb_funcall(rb_funcall1(INT2FIX(1), '+', 
			rb_funcall1(x, '*', x)), sqrt, 1, prec)), '/', x);
	x = atan_func(x, prec);
	if (dbl)
		x = rb_funcall(x, add, 2, x, prec);
	if (inv)
		x = rb_funcall(
			rb_funcall(pi, div, 2, INT2FIX(2), prec),
		sub, 2, x, prec);
	if (neg)
		x = rb_num_uminus(x);
	return x;
}

VALUE
rb_bigmath_atan(VALUE x, VALUE prec)
{
	return rb_bigmath_atan_cb(x, prec, atan_euler_ser);
}
