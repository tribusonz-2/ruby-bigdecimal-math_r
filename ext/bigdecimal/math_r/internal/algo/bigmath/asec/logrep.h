VALUE
asec_logrep(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	const ID sub = rb_intern("sub");
	VALUE t, pi_2, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	x = rb_num_canonicalize(x, n, ARG_REAL, ARG_RECIPROCAL);
	t = rb_funcall1(x, '*', x);
	t = rb_funcall1(INT2FIX(1), '-', t);
	t = rb_bigmath_sqrt(t, n);
	t = rb_funcall1(x, '/', t);
	t = rb_bigmath_atan(t, n);
	pi_2 = rb_funcall(
		rb_bigmath_const_pi(n), div, 2, INT2FIX(2), n);
	t = rb_funcall(pi_2, sub, 2, t, n);

	return rb_num_round(t, prec);
}
