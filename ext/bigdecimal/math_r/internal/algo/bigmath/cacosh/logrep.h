VALUE
cacosh_logrep(VALUE z, VALUE prec)
{
	VALUE c1, c2, c3, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	c2 = rb_funcall1(z, '+', BIG_ONE);
	c2 = rb_bigmath_csqrt(c2, n);
	c3 = rb_funcall1(z, '-', BIG_ONE);
	c3 = rb_bigmath_csqrt(c3, n);
	c1 = rb_funcall1(c2, '*', c3);
	c1 = rb_funcall1(z, '+', c1);
	c1 = rb_bigmath_clog(c1, n);

	return rb_num_round(c1, prec);
}
