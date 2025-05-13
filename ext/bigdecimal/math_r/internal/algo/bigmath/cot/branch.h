VALUE
cot_branch(VALUE x, VALUE prec, bigmath_func1 cot_cb)
{
	VALUE w = Qundef;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (!rb_num_finite_p(x))
		w = BIG_NAN;
	else if (rb_num_infinite_p(x) != 0)
		w = rb_num_infinite_p(x) ? BIG_MINUS_ZERO : BIG_ZERO;
	else
	{
		VALUE t = Qundef;
		VALUE v_sin = Qundef, v_cos = Qundef;
		x = rb_bigmath_to_rad(x, prec, &t);
		if (-1 != rb_bigmath_degree_sparg(t, prec, &v_sin, &v_cos))
		{
			const ID div = rb_intern("div");
			w = rb_funcall(v_cos, div, 2, v_sin, prec);
		}
		else
			w = cot_cb(x, prec);
	}

	return w;
}

