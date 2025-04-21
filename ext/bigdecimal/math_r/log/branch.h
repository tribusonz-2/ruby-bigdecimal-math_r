VALUE
log_branch(VALUE x, VALUE prec, bigmath_func1 log_cb)
{
	VALUE y = Qundef;

	rb_check_precise(prec);
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (!rb_num_finite_p(x))
	{
		switch (rb_num_infinite_p(x)) {
		case 1:
			y = BIG_INF;
			break;
		case -1: case 0:
		default:
			y = BIG_NAN;
			break;
		}
	}
	else if (rb_num_zero_p(x))
	{
		y = BIG_MINUS_INF;
	}
        else
        {
		if (TYPE(x) == T_COMPLEX)
			rb_raise(rb_eTypeError, "no solution for complex");
		if (rb_num_positive_p(x))
			y = log_cb(x, prec);
		else
			y = BIG_NAN;
	}
	return y;
}

