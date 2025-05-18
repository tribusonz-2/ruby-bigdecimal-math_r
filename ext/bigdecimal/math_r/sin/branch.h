VALUE
sin_branch(VALUE x, VALUE prec, bigmath_func1 sin_cb)
{
	VALUE w = Qundef;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (!rb_num_finite_p(x))
		w = BIG_NAN;
	else
	{
		VALUE t = Qundef;
		VALUE v_sin = Qundef;
		x = rb_bigmath_to_rad(x, prec, &t);
		if (-1 != rb_bigmath_degree_sparg(t, prec, &v_sin, NULL))
			w = v_sin;
		else
			w = sin_cb(x, prec);
	}

	return w;
}

