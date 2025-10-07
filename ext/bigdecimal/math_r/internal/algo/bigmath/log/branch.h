VALUE
log_branch(VALUE x, VALUE prec, bigmath_func1 log_cb)
{
	VALUE y = Qundef, n;

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
		if (rb_num_positive_p(x))
		{
			const ID add = rb_intern("add");
			VALUE exp, fra;

			rb_check_precise(prec);
			n = rb_numdiff_make_n(prec);

			fra = rcm2_edf(x, &exp);
			exp = rb_funcall1(rb_bigmath_const_log2(n), '*', exp);
			fra = log_cb(fra, prec);
			y = rb_funcall(exp, add, 2, fra, prec);
		}
		else
			y = BIG_NAN;
	}
	return y;
}

