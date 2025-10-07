VALUE
casinh_logrep(VALUE z, VALUE prec)
{
	VALUE n, t, y;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	t = rb_funcall1(rb_funcall1(z, '*', z), '+', BIG_ONE);
	t = rb_bigmath_csqrt(t, n);
	y = rb_bigmath_clog(rb_funcall1(z, '+', t), n);

	return rb_num_round(y, prec);
}
