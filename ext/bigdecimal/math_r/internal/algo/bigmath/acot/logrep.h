VALUE
acot_logrep(VALUE x, VALUE prec)
{
	VALUE n1, m1, y, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RECIPROCAL);
	n1 = rb_Complex(BIG_ONE, x);
	m1 = rb_bigmath_sqrt(rb_funcall1(BIG_ONE, '+', rb_funcall1(x, '*', x)), n);
	y = rb_funcall1(n1, '/', m1);
	y = rb_bigmath_carg(y, n);

	return rb_num_round(y, prec);
}
