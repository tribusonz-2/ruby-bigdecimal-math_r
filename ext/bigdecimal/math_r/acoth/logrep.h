VALUE
acoth_logrep(VALUE x, VALUE prec)
{
	VALUE y;

	y = rb_funcall1(
		rb_funcall1(x, '+', BIG_ONE), '/', 
		rb_funcall1(x, '-', BIG_ONE));
	y = rb_bigmath_log(y, prec);
	y = rb_funcall1(rb_Rational(INT2FIX(1), INT2FIX(2)), '*', y);
	y = rb_num_round(y, prec);

	return y;
}


#if 0
VALUE
acoth_logrep(VALUE x, VALUE prec)
{
	VALUE r1, r2, r3, r4;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RECIPROCAL);
	r1 = rb_funcall1(BIG_ONE, '+', x);
	r2 = rb_bigmath_sqrt(r1, prec);
	r1 = rb_funcall1(BIG_ONE, '-', x);
	r3 = rb_bigmath_sqrt(r1, prec);
	r4 = rb_funcall1(r2, '/', r3);
	r4 = rb_bigmath_log(r4, prec);

	return rb_num_round(r4, prec);
}
#endif
