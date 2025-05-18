VALUE
csch_branch(VALUE x, VALUE prec, bigmath_func1 csch_cb)
{
	VALUE y = Qundef;
	int sign;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (rb_num_nan_p(x))
		y = BIG_NAN;
	else if ((sign = rb_num_infinite_p(x)) != 0)
		y = sign == 1 ? BIG_ZERO : BIG_MINUS_ZERO;
	else
	{
		VALUE absx = rb_num_negative_p(x) ? rb_num_uminus(x) : x;
		if (RTEST(rb_num_coerce_cmp(absx, INT2FIX(3), '<')))
			y = csch_ser(x, prec);
		else
			y = csch_cb(x, prec);
	}

	return y;
}
