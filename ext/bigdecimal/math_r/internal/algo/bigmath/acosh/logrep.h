VALUE
acosh_logrep(VALUE x, VALUE prec)
{
	VALUE n, t, y;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	t = rb_funcall1(rb_funcall1(x, '*', x), '-', BIG_ONE);
	t = rb_bigmath_sqrt(t, n);
	y = rb_bigmath_log(rb_funcall1(x, '+', t), n);

	return rb_num_round(y, prec);
}
