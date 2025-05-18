VALUE
atan_logrep(VALUE x, VALUE prec)
{
	VALUE n, m, y;

	rb_check_precise(prec);

	n = rb_Complex(BIG_ONE, x);
	m = rb_bigmath_sqrt(rb_funcall1(BIG_ONE, '+', rb_funcall1(x, '*', x)), prec);
	y = rb_funcall1(n, '/', m);
	y = rb_bigmath_carg(y, prec);

	return y;
}
