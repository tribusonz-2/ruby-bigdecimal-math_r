VALUE
hypot_branch(VALUE a, VALUE b, VALUE prec, bigmath_func2 hypot_cb)
{
	VALUE c = Qundef;
	if (hypot_cb == NULL)  return BIG_NAN;
	rb_check_precise(prec);
	a = rb_num_real_p(a) ?
		rb_num_canonicalize(a, prec, ARG_REAL, ARG_RAWVALUE) :
		rb_num_canonicalize(a, prec, ARG_COMPLEX, ARG_RAWVALUE);
	b = rb_num_real_p(b) ?
		rb_num_canonicalize(b, prec, ARG_REAL, ARG_RAWVALUE) :
		rb_num_canonicalize(b, prec, ARG_COMPLEX, ARG_RAWVALUE);
	if (!rb_num_finite_p(a) || !rb_num_finite_p(b))
	{
		if (rb_num_nan_p(a) || rb_num_nan_p(b))
			c = BIG_NAN;
		else if (rb_num_infinite_p(a) || rb_num_infinite_p(b))
			c = BIG_INF;
	}
	if (c == Qundef)
		c = hypot_cb(a, b, prec);

	return c;
}

