VALUE
catan_logrep(VALUE z, VALUE prec)
{
	VALUE c1, c2, c3;

	rb_check_precise(prec);

	c1 = rb_ImaginaryZ(z, SIGN_PLUS);
	c2 = rb_funcall1(rb_Complex(BIG_ONE, rb_num_uminus(z)), '/', 
	                 rb_Complex(BIG_ONE, z));
	c3 = rb_bigmath_clog(c2, prec);

	c1 = rb_Complex(INT2FIX(0), rb_Rational(INT2FIX(1), INT2FIX(2)));
	c2 = rb_funcall1(c1, '*', c3);

	return rb_num_round(c2, prec);
}
