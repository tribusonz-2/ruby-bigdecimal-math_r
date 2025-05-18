VALUE
cacos_logrep(VALUE z, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE c1, c2, c3, c4, c5, c6;

	c1 = rb_ImaginaryZ(z, SIGN_PLUS);
	c2 = rb_bigmath_csqrt(rb_funcall1(BIG_ONE, '-', 
		rb_funcall1(z, '*', z)), prec);
	c3 = rb_bigmath_clog(rb_funcall1(c1, '+', c2), prec);
	c4 = rb_ImaginaryZ(c3, SIGN_PLUS);
	c5 = rb_funcall(rb_bigmath_const_pi(prec), div, 2, INT2FIX(2), prec);
	c6 = rb_funcall1(c5, '+', c4);

	return rb_num_round(c6, prec);
}
