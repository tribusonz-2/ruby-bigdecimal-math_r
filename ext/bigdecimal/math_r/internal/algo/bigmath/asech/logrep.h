VALUE
asech_logrep(VALUE x, VALUE prec)
{
	VALUE y, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	y = rb_funcall1(x, '*', x);
	y = rb_funcall1(BIG_ONE, '-', y);
	y = rb_bigmath_sqrt(y, n);
	y = rb_funcall1(y, '+', BIG_ONE);
	y = rb_funcall1(y, '/', x);
	y = rb_bigmath_log(y, prec);
	return y;
}
