VALUE
casinh_branch(VALUE z, VALUE prec, bigmath_func1 casinh_cb)
{
	VALUE y = Qundef;

	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);

	if (!rb_num_finite_p(z))
	{
		if (rb_num_infinite_p(rb_num_imag(z)) == 0)
		{
			switch (rb_num_infinite_p(rb_num_real(z))) {
			case 1:
				y = rb_Complex(BIG_INF, BIG_ZERO);
				break;
			case -1:
				y = rb_Complex(BIG_MINUS_INF, BIG_ZERO);
				break;
			}
		}
		else if (rb_num_infinite_p(rb_num_real(z)) == 0)
		{
			if (rb_num_zero_p(rb_num_real(z)))
			{
				switch (rb_num_infinite_p(rb_num_imag(z))) {
				case 1:
					y = rb_Complex(BIG_INF, rb_bigmath_const_pi(prec));
					break;
				case -1:
					y = rb_Complex(BIG_ZERO, BIG_ZERO);
					break;
				}
			}
			else
			{
				const ID div = rb_intern("div");
				VALUE pi_2 = rb_funcall(rb_bigmath_const_pi(prec), div, 2, INT2FIX(2), prec);
				switch (rb_num_infinite_p(rb_num_imag(z))) {
				case 1:
					y = rb_Complex(BIG_INF, pi_2);
					break;
				case -1:
					pi_2 = rb_num_uminus(pi_2);
					y = rb_Complex(BIG_ZERO, pi_2);
					break;
				}
			}
		}
		else
		{
			y = rb_Complex(BIG_NAN, BIG_NAN);
		}
	}
	if (y == Qundef)
	{
		y = casinh_cb(z, prec);
	}
	return y;
}
