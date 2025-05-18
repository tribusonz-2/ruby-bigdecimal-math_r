VALUE
acos_logrep(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	const ID sub = rb_intern("sub");
	VALUE t, pi_2;

	rb_check_precise(prec);

	t = rb_funcall1(x, '*', x);
	t = rb_funcall1(INT2FIX(1), '-', t);
	t = rb_bigmath_sqrt(t, prec);
	t = rb_funcall1(x, '/', t);
	t = rb_bigmath_atan(t, prec);
	pi_2 = rb_funcall(rb_bigmath_const_pi(prec), div, 2, INT2FIX(2), prec);
	t = rb_funcall(pi_2, sub, 2, t, prec);

	return t;
}
