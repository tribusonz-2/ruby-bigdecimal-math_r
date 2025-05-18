VALUE
asin_edom(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE imag, y, arg, t;

	rb_check_precise(prec);

	t = rb_funcall1(BIG_ONE, '-', rb_funcall1(x, '*', x));
	t = rb_funcall1(rb_bigmath_sqrt(rb_num_uminus(t), prec), '+', x);
	arg = rb_funcall(
		rb_bigmath_const_pi(prec), div, 2, INT2FIX(2), prec);
	if (!rb_num_negative_p(x))
		arg = rb_num_uminus(arg);
	imag = rb_bigmath_log(rb_num_abs(t), prec);
	y = rb_Complex(arg, imag);
	y = rb_num_uminus(y);

	return y;
}
