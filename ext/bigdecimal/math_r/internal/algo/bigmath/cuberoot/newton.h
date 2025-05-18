VALUE
cuberoot_newton(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE s = Qundef, t = Qundef, prev = Qundef;
	VALUE two, three;
	bool positive;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	rb_check_precise(prec);

	if (!rb_num_finite_p(x) || rb_num_zero_p(x))
		return x;
	positive = rb_num_positive_p(x) ? true : false;

	if (!positive)
		x = rb_num_uminus(x);

	if (RTEST(rb_num_coerce_cmp(x, INT2FIX(1), '>')))
		s = x;
	else
		s = BIG_ONE;

	two = rb_BigDecimal1(INT2FIX(2));
	three = rb_BigDecimal1(INT2FIX(3));

	do {
		prev = s;
		t = rb_funcall1(s, '*', s);
		t = rb_funcall1(x, '/', t);
		t = rb_funcall1(t, '+', rb_funcall1(two, '*', s));
		s = rb_funcall(t, div, 2, three, prec);
	} while (RTEST(rb_num_coerce_cmp(s, prev, '<')));

	RB_GC_GUARD(s);
	RB_GC_GUARD(t);
	RB_GC_GUARD(prev);
	RB_GC_GUARD(two);
	RB_GC_GUARD(three);

	return positive ? prev : rb_num_uminus(prev);
}
