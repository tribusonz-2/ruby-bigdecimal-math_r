VALUE
casin_logrep(VALUE z, VALUE prec)
{
	VALUE c1, c2, c3, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	c1 = rb_ImaginaryZ(z, SIGN_PLUS);
	c2 = rb_bigmath_csqrt(
		rb_funcall1(BIG_ONE, '-', rb_funcall1(z, '*', z)), n);
	c3 = rb_bigmath_clog(rb_funcall1(c1, '+', c2), n);
	z = rb_ImaginaryZ(c3, SIGN_MINUS);

	return rb_num_round(z, prec);
}
