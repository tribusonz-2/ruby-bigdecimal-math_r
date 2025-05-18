VALUE
cosh_branch(VALUE x, VALUE prec, bigmath_func1 cosh_cb)
{
	VALUE y = Qundef;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (rb_num_nan_p(x))
		y = BIG_NAN;
	else if (rb_num_infinite_p(x) != 0)
		y = BIG_INF;
	else
	{
		VALUE absx = rb_num_negative_p(x) ? rb_num_uminus(x) : x;
		if (RTEST(rb_num_coerce_cmp(absx, INT2FIX(3), '<')))
			y = cosh_ser(x, prec);
		else
			y = cosh_cb(x, prec);
	}

	return y;
}
