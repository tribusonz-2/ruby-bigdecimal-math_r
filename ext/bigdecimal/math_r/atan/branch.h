VALUE
atan_branch(VALUE x, VALUE prec, bigmath_func1 atan_cb)
{
	const ID add = rb_intern("add");
	const ID sub = rb_intern("sub");
	const ID div = rb_intern("div");
	const ID round = rb_intern("round");
	const ID sqrt = rb_intern("sqrt");
	bool neg, dbl, inv;
	VALUE pi;
	rb_check_precise(prec);
	if (atan_cb == NULL)
		return BIG_NAN;
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
	x = atan_cb(x, prec);
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
