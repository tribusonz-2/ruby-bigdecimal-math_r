VALUE
cexp2_branch(VALUE z, VALUE prec, bigmath_func1 cexp2_cb)
{
	VALUE w = Qundef;

	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);

	if (!rb_num_finite_p(z))
	{
		int real_sign;
		if (rb_num_nan_p(z))
		{
			if (rb_num_zero_p(rb_num_imag(z)))
				w = rb_Complex(BIG_NAN, BIG_ZERO);
			else
				w = rb_Complex(BIG_NAN, BIG_NAN);
		}
		else if ((real_sign = rb_num_infinite_p(rb_num_real(z))) != 0 &&
		          rb_num_finite_p(rb_num_imag(z)))
		{
			switch (real_sign) {
			case -1:
				w = rb_Complex(BIG_ZERO, BIG_ZERO);
				break;
			case 1:
				w = rb_Complex(BIG_INF, BIG_ZERO);
				break;
			}
		}
                else
		{
			w = rb_Complex(BIG_NAN, BIG_NAN);
		}
	}
	if (w == Qundef)
	{
		VALUE real = rb_num_real(z), imag = rb_num_imag(z);
		imag = rb_bigmath_to_rad(imag, prec, NULL);
		w = cexp2_cb(rb_Complex(real, imag), prec);
	}
	return w;
}
