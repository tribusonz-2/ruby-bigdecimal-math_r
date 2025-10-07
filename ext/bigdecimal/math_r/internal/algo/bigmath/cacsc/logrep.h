VALUE
cacsc_logrep(VALUE z, VALUE prec)
{
	VALUE y, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	y = rb_funcall1(z, '*', z);
	y = rb_funcall1(BIG_ONE, '/', y);
	y = rb_funcall1(BIG_ONE, '-', y);
	y = rb_bigmath_csqrt(y, n);
	y = rb_Complex(y, 
		rb_num_canonicalize(
			rb_num_uminus(z), n, ARG_COMPLEX, ARG_RECIPROCAL));
	y = rb_bigmath_clog(y, n);
	y = rb_ImaginaryZ(y, SIGN_PLUS);

	return rb_num_round(y, prec);
}
