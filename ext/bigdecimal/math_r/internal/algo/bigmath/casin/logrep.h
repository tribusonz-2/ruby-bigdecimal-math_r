VALUE
casin_logrep(VALUE z, VALUE prec)
{
	VALUE c1, c2, c3;

	rb_check_precise(prec);

	c1 = rb_ImaginaryZ(z, SIGN_PLUS);
	c2 = rb_bigmath_csqrt(
		rb_funcall1(BIG_ONE, '-', rb_funcall1(z, '*', z)), prec);
	c3 = rb_bigmath_clog(rb_funcall1(c1, '+', c2), prec);

	return rb_ImaginaryZ(c3, SIGN_MINUS);
}
