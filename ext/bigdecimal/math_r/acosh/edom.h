VALUE
acosh_edom(VALUE x, VALUE prec)
{
	const ID add = rb_intern("add");
	const ID div = rb_intern("div");
	VALUE t, w, y;

	rb_check_precise(prec);

	t = rb_funcall1(BIG_MINUS_ONE, '+', rb_funcall1(x, '*', x));
	w = rb_funcall(rb_bigmath_sqrt(rb_num_uminus(t), prec), div, 2, x, prec);
	y = rb_bigmath_atan(w, prec);
	if (rb_num_negative_p(x))
		y = rb_funcall(rb_bigmath_const_pi(prec), add, 2, y, prec);

	return rb_Complex(BIG_ZERO, y);
}
