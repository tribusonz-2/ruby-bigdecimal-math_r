VALUE
asec_edom(VALUE x, VALUE prec)
{
	VALUE imag, y, arg, t, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	x = rb_num_canonicalize(x, n, ARG_REAL, ARG_RECIPROCAL);
	t = rb_funcall1(BIG_ONE, '-', rb_funcall1(x, '*', x));
	t = rb_funcall1(rb_bigmath_sqrt(rb_num_uminus(t), n), '+', x);
	arg = rb_num_negative_p(x) ? rb_bigmath_const_pi(n) : BIG_ZERO;
	imag = rb_bigmath_log(rb_num_abs(t), n);
	y = rb_Complex(arg, imag);

	return rb_num_round(y, prec);
}
