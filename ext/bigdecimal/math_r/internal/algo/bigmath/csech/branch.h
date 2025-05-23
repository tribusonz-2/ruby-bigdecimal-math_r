VALUE
csech_branch(VALUE z, VALUE prec, bigmath_func1 csech_cb)
{
	VALUE w = Qundef;
	if (!rb_num_finite_p(z))
	{
		if (rb_num_infinite_p(z) != 0 && rb_num_zero_p(rb_num_imag(z)))
		{
			w = rb_Complex(BIG_ZERO, BIG_ZERO);
		}
		else
		{
			w = BIG_NAN;
			if (rb_num_nan_p(rb_num_real(w)) && rb_num_zero_p(rb_num_imag(z)))
				w = rb_Complex(w, BIG_ZERO);
			else
				w = rb_Complex(w, BIG_NAN);
		}
	}
	if (w == Qundef)
	{
		VALUE real = rb_num_real(z), imag = rb_num_imag(z);
		VALUE t = Qundef;
		VALUE v_cos = Qundef;
		imag = rb_bigmath_to_rad(imag, prec, &t);
		if (-1 != rb_bigmath_degree_sparg(t, prec, NULL, &v_cos) &&
		    rb_num_zero_p(real))
		{
			v_cos = rb_num_canonicalize(v_cos, prec, ARG_REAL, ARG_RECIPROCAL);
			w = rb_Complex(BIG_ZERO, v_cos);
		}
		else
		{
			w = csech_cb(rb_Complex(real, imag), prec);
		}
	}
	return w;
}
