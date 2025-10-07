VALUE
acsc_logrep(VALUE x, VALUE prec)
{
	VALUE t, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	x = rb_num_canonicalize(x, n, ARG_REAL, ARG_RECIPROCAL);
	t = rb_funcall1(x, '*', x);
	t = rb_funcall1(INT2FIX(1), '-', t);
	t = rb_bigmath_sqrt(t, n);
	t = rb_funcall1(x, '/', t);
	t = rb_bigmath_atan(t, n);

	return rb_num_round(t, prec);
}
