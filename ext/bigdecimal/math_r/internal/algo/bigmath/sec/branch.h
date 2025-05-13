VALUE
sec_branch(VALUE x, VALUE prec, bigmath_func1 sec_cb)
{
	VALUE w = Qundef;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (rb_num_nan_p(x))
		w = BIG_NAN;
	else if (rb_num_infinite_p(x) != 0)
	{
		w = BIG_ONE;
	}
	else
	{
		VALUE t = Qundef;
		VALUE v_cos = Qundef;
		x = rb_bigmath_to_rad(x, prec, &t);
		if (-1 != rb_bigmath_degree_sparg(t, prec, NULL, &v_cos))
		{
			w = rb_num_canonicalize(v_cos, prec, ARG_REAL, ARG_RECIPROCAL);
		}
		else
			w = sec_cb(x, prec);
	}
	return w;
}
