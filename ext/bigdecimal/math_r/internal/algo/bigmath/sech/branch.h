VALUE
sech_branch(VALUE x, VALUE prec, bigmath_func1 sech_cb)
{
	VALUE y = Qundef;
	rb_check_precise(prec);
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	if (rb_num_nan_p(x))
		y = BIG_NAN;
	else if (rb_num_infinite_p(x) != 0)
		y = BIG_ZERO;
	else
	{
		VALUE absx = rb_num_negative_p(x) ? rb_num_uminus(x) : x;
		if (RTEST(rb_num_coerce_cmp(absx, INT2FIX(3), '<')))
			y = sech_ser(x, prec);
		else
			y = sech_cb(x, prec);
	}
	return y;
}
