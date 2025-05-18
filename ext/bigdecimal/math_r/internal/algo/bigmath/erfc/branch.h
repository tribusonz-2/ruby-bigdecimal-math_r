VALUE
erfc_branch(VALUE x, VALUE prec, bigmath_func1 erfc_cb)
{
	VALUE y = Qundef;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (!rb_num_finite_p(x))
	{
		if (rb_num_nan_p(x))
			y = BIG_NAN;
		else
			y = rb_num_negative_p(x) ? rb_BigDecimal1(INT2FIX(2)) : BIG_ZERO;
	}
	if (y == Qundef)
		y = erfc_cb(x, prec);
	return y;
}
