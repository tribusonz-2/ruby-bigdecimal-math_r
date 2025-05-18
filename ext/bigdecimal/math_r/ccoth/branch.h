VALUE
ccoth_branch(VALUE z, VALUE prec, bigmath_func1 ccoth_cb)
{
	VALUE w = Qundef;
	
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	
	if (!rb_num_finite_p(z))
	{
		if (rb_num_infinite_p(z) != 0 && rb_num_zero_p(rb_num_imag(z)))
		{
			w = rb_num_negative_p(rb_num_real(z)) ? BIG_MINUS_ONE : BIG_ONE;
			w = rb_Complex(w, BIG_ZERO);
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
		VALUE v_sin = Qundef, v_cos = Qundef;
		imag = rb_bigmath_to_rad(imag, prec, &t);
		if (-1 != rb_bigmath_degree_sparg(t, prec, &v_sin, &v_cos) &&
		    rb_num_zero_p(real))
		{
			const ID div = rb_intern("div");
			w = rb_funcall(v_cos, div, 2, v_sin, prec);
			w = rb_Complex(BIG_ZERO, w);
		}
		else
		{
			w = ccoth_cb(rb_Complex(real, imag), prec);
		}
	}
	return w;
}
