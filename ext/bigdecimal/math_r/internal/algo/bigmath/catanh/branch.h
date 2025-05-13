VALUE
catanh_branch(VALUE z, VALUE prec, bigmath_func1 catanh_cb)
{
	VALUE w = Qundef;

	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);

	if (rb_num_nan_p(z))
		w = rb_Complex(BIG_NAN, BIG_NAN);
	else if (rb_num_infinite_p(z) != 0)
	{
		const ID div = rb_intern("div");
		VALUE pi_2 = rb_funcall(
			rb_bigmath_const_pi(prec), div, 2, INT2FIX(2), prec);
		if (rb_num_negative_p(rb_num_imag(z)))
			pi_2 = rb_num_uminus(pi_2);
		w = rb_Complex(BIG_ZERO, pi_2);
	}
	else
	{
		z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
		w = catanh_cb(z, prec);
	}

	return w;
}
