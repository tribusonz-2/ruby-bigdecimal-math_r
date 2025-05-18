VALUE
cacoth_branch(VALUE z, VALUE prec, bigmath_func1 catanh_cb)
{
	VALUE w = Qundef;

	if (rb_num_nan_p(z))
	{
		w = rb_Complex(BIG_NAN, BIG_NAN);
	}
	else if (rb_num_infinite_p(z) != 0)
	{
		w = rb_Complex(BIG_ZERO, BIG_ZERO);
	}
	else if (rb_num_zero_p(z))
	{
		const ID div = rb_intern("div");
		VALUE pi_2 = rb_funcall(
			rb_bigmath_const_pi(prec), div, 2, 
			INT2FIX(2), prec);
		w = rb_Complex(BIG_ZERO, pi_2);
	}
	else
	{
		z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
		w = catanh_cb(z, prec);
	}

	return w;
}
