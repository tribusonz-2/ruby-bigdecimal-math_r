VALUE
rb_bigmath_to_rad(VALUE x, VALUE prec, VALUE *t)
{
	const ID mult = rb_intern("mult");
	VALUE n = rb_numdiff_make_n(prec);
	VALUE twopi = rb_bigmath_const_pi(n); twopi = rb_funcall1(twopi, '*', INT2FIX(2));
	bool neg = false;
	if (NUM2INT(rb_num_cmpeql(x, rb_num_uminus(twopi))) == -1 ||
	    NUM2INT(rb_num_cmpeql(twopi, x)) == -1)
	{
		neg = rb_num_negative_p(x);
		if (neg)
			x = rb_num_uminus(x);
		if (rb_num_cmpeql(x, INT2FIX(30)) == 1)
			x = rb_funcall1(x, '%', twopi);
		else
			while (RTEST(rb_num_coerce_cmp(x, twopi, '>')))
				x = rb_funcall1(x, '-', twopi);
		if (neg)
			x = rb_num_uminus(x);
	}
	else
	{
		x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	}
	if (t != NULL)
	{
		*t = rb_num_round(
			rb_funcall1(x, '/', twopi), prec);
		if (rb_num_negative_p(*t))
			rb_funcall1(x, '+', INT2FIX(1));
		*t = rb_funcall(*t, mult, 2, INT2FIX(360), prec);
	}
#if 0
	if (NUM2INT(rb_num_cmpeql(x, rb_num_uminus(pi))) == -1)
		x = rb_funcall1(x, '+', twopi);
	else if   (NUM2INT(rb_num_cmpeql(pi, x)) == -1)
		x = rb_funcall1(x, '-', twopi);
#endif
	return x;
}
