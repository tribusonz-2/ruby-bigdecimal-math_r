VALUE
csin_branch(VALUE z, VALUE prec, bigmath_func1 csin_cb)
{
	VALUE w = Qundef;

	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);

	if (!rb_num_finite_p(z))
	{
		if (rb_num_nan_p(z) || rb_num_finite_p(rb_num_imag(z)))
		{
			if (rb_num_zero_p(rb_num_imag(z)))
				w = rb_Complex(BIG_NAN, BIG_ZERO);
			else
				w = rb_Complex(BIG_NAN, BIG_NAN);
		}
		else if (rb_num_finite_p(rb_num_real(z)))
		{
			if (rb_num_negative_p(rb_num_imag(z)))
				w = rb_Complex(BIG_ZERO, BIG_MINUS_INF);
			else
				w = rb_Complex(BIG_ZERO, BIG_INF);
		}
		else
			w = rb_Complex(BIG_NAN, BIG_NAN);
	}
	if (w == Qundef)
	{
		VALUE real = rb_num_real(z), imag = rb_num_imag(z);
		VALUE t = Qundef;
		VALUE v_sin = Qundef;
		real = rb_bigmath_to_rad(real, prec, &t);
		if (-1 != rb_bigmath_degree_sparg(t, prec, &v_sin, NULL) &&
		    rb_num_zero_p(imag))
		{
			w = rb_Complex(v_sin, BIG_ZERO);
		}
		else
		{
			w = csin_cb(rb_Complex(real, imag), prec);
		}
	}
	return w;
}
