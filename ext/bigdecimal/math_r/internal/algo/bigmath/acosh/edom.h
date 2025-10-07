VALUE
acosh_edom(VALUE x, VALUE prec)
{
	const ID add = rb_intern("add");
	const ID div = rb_intern("div");
	VALUE t, w, y, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	t = rb_funcall1(BIG_MINUS_ONE, '+', rb_funcall1(x, '*', x));
	w = rb_funcall(rb_bigmath_sqrt(rb_num_uminus(t), prec), div, 2, x, n);
	y = rb_bigmath_atan(w, n);
	if (rb_num_negative_p(x))
		y = rb_funcall(rb_bigmath_const_pi(n), add, 2, y, n);
	y = rb_Complex(BIG_ZERO, y);

	return rb_num_round(y, prec);
}
