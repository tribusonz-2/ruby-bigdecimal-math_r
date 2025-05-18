VALUE
tan_branch(VALUE x, VALUE prec, bigmath_func1 tan_cb)
{
	VALUE w = Qundef;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (!rb_num_finite_p(x))
		w = BIG_NAN;
	else
	{
		VALUE t = Qundef;
		VALUE v_sin = Qundef, v_cos;
		x = rb_bigmath_to_rad(x, prec, &t);
		if (-1 != rb_bigmath_degree_sparg(t, prec, &v_sin, &v_cos))
		{
			const ID div = rb_intern("div");
			w = rb_funcall(v_sin, div, 2, v_cos, prec);
		}
		else
			w = tan_cb(x, prec);
	}

	return w;
}

