VALUE
cacot_logrep(VALUE z, VALUE prec)
{
	VALUE c1, c2, c3, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	c1 = rb_ImaginaryZ(z, SIGN_PLUS);
	c2 = rb_funcall1(rb_funcall1(c1, '-', BIG_ONE), '/', 
	                 rb_funcall1(c1, '+', BIG_ONE));
	c3 = rb_bigmath_clog(c2, n);

	c1 = rb_funcall1(rb_Complex(INT2FIX(0), INT2FIX(1)), '/', INT2FIX(2));
	c2 = rb_funcall1(rb_num_uminus(c1), '*', c3);

	return rb_num_round(c2, prec);
}
