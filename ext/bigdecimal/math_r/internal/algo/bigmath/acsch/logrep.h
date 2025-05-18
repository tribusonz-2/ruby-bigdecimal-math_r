VALUE
acsch_logrep(VALUE x, VALUE prec)
{
	VALUE t, y;

	rb_check_precise(prec);

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RECIPROCAL);
	if (rb_num_positive_p(x))
	{
		t = rb_funcall1(rb_funcall1(x, '*', x), '+', BIG_ONE);
		t = rb_bigmath_sqrt(t, prec);
		y = rb_bigmath_log(rb_funcall1(x, '+', t), prec);
	}
	else if (rb_num_negative_p(x))
	{
		t = rb_funcall1(rb_funcall1(x, '*', x), '+', BIG_ONE);
		t = rb_bigmath_sqrt(t, prec);
		t = rb_bigmath_log(rb_funcall1(t, '-', x), prec);
		y = rb_num_uminus(t);
	}
	else 
		y = BIG_ZERO;
	return rb_num_round(y, prec);
}
