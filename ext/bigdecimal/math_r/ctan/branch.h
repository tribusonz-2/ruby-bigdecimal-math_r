VALUE
ctan_branch(VALUE z, VALUE prec, bigmath_func1 ctan_cb)
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
				w = rb_Complex(BIG_ZERO, BIG_MINUS_ONE);
			else
				w = rb_Complex(BIG_ZERO, BIG_ONE);
		}
		else
			w = rb_Complex(BIG_NAN, BIG_NAN);
	}
	if (w == Qundef)
	{
		VALUE real = rb_num_real(z), imag = rb_num_imag(z);
		VALUE t = Qundef;
		VALUE v_sin = Qundef, v_cos = Qundef;
		real = rb_bigmath_to_rad(real, prec, &t);
		if (-1 != rb_bigmath_degree_sparg(t, prec, &v_sin, &v_cos) &&
		    rb_num_zero_p(imag))
		{
			const ID div = rb_intern("div");
			w = rb_funcall(v_sin, div, 2, v_cos, prec);
			w = rb_Complex(w, BIG_ZERO);
		}
		else
		{
			w = ctan_cb(rb_Complex(real, imag), prec);
		}
	}
	return w;
}
