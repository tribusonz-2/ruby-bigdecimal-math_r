VALUE
asinh_logrep(VALUE x, VALUE prec)
{
	VALUE t, y, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	if (rb_num_positive_p(x))
	{
		t = rb_funcall1(rb_funcall1(x, '*', x), '+', BIG_ONE);
		t = rb_bigmath_sqrt(t, n);
		y = rb_bigmath_log(rb_funcall1(x, '+', t), n);
	}
	else if (rb_num_negative_p(x))
	{
		t = rb_funcall1(rb_funcall1(x, '*', x), '+', BIG_ONE);
		t = rb_bigmath_sqrt(t, n);
		t = rb_bigmath_log(rb_funcall1(t, '-', x), n);
		y = rb_num_uminus(t);
	}
	else 
		y = BIG_ZERO;
	return rb_num_round(y, prec);
}
