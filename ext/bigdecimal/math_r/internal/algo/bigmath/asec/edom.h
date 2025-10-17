VALUE
asec_edom(VALUE x, VALUE prec)
{
	VALUE imag, y, arg, t, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	x = rb_num_canonicalize(x, n, ARG_REAL, ARG_RECIPROCAL);
	t = rb_funcall1(BIG_ONE, '-', rb_funcall1(x, '*', x));
	// Bug-fix: Below, if the argument is -0.0, the calculation is Infinity-Infinity, resulting in NaN.
	t = rb_funcall1(rb_bigmath_sqrt(rb_num_uminus(t), n), '+', x);
	arg = rb_num_negative_p(x) ? rb_bigmath_const_pi(n) : BIG_ZERO;
	imag = rb_bigmath_log(rb_num_abs(t), n);
	// Bug-Fix: Set to -Infinity if NaN
	if (rb_num_nan_p(imag))
		imag = BIG_MINUS_INF;
	y = rb_Complex(arg, imag);

	return rb_num_round(y, prec);
}
