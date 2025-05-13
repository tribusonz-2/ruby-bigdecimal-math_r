VALUE
cacsc_logrep(VALUE z, VALUE prec)
{
	VALUE y;

	rb_check_precise(prec);

	y = rb_funcall1(z, '*', z);
	y = rb_funcall1(BIG_ONE, '/', y);
	y = rb_funcall1(BIG_ONE, '-', y);
	y = rb_bigmath_csqrt(y, prec);
	y = rb_Complex(y, 
		rb_num_canonicalize(
			rb_num_uminus(z), prec, ARG_COMPLEX, ARG_RECIPROCAL));
	y = rb_bigmath_clog(y, prec);
	y = rb_ImaginaryZ(y, SIGN_PLUS);

	return rb_num_round(y, prec);
}
