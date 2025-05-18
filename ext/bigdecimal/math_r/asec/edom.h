VALUE
asec_edom(VALUE x, VALUE prec)
{
	VALUE imag, y, arg, t;

	rb_check_precise(prec);

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RECIPROCAL);
	t = rb_funcall1(BIG_ONE, '-', rb_funcall1(x, '*', x));
	t = rb_funcall1(rb_bigmath_sqrt(rb_num_uminus(t), prec), '+', x);
	arg = rb_num_negative_p(x) ? rb_bigmath_const_pi(prec) : BIG_ZERO;
	imag = rb_bigmath_log(rb_num_abs(t), prec);
	y = rb_Complex(arg, imag);

	return y;
}
