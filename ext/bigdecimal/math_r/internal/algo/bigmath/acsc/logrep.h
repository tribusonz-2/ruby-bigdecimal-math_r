VALUE
acsc_logrep(VALUE x, VALUE prec)
{
	VALUE t;

	rb_check_precise(prec);

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RECIPROCAL);
	t = rb_funcall1(x, '*', x);
	t = rb_funcall1(INT2FIX(1), '-', t);
	t = rb_bigmath_sqrt(t, prec);
	t = rb_funcall1(x, '/', t);
	t = rb_bigmath_atan(t, prec);

	return t;
}
