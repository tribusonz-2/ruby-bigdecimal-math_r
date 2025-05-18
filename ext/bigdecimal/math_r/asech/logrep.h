VALUE
asech_logrep(VALUE x, VALUE prec)
{
	VALUE y;

	rb_check_precise(prec);

	y = rb_funcall1(x, '*', x);
	y = rb_funcall1(BIG_ONE, '-', y);
	y = rb_bigmath_sqrt(y, prec);
	y = rb_funcall1(y, '+', BIG_ONE);
	y = rb_funcall1(y, '/', x);
	y = rb_bigmath_log(y, prec);

	return y;
}
