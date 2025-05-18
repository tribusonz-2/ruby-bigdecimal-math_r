VALUE
pow_formula(VALUE x, VALUE y, VALUE prec)
{
	VALUE a = Qundef;

	rb_check_precise(prec);
	if (!rb_num_real_p(x))
		rb_raise(rb_eTypeError, "not a Real");
	if (rb_num_zero_p(rb_num_real(x)))
		a = BIG_ONE;
	if (TYPE(y) == T_FIXNUM || TYPE(y) == T_BIGNUM)
	{
		if (rb_num_positive_p(rb_num_real(x)))
			a = ipow_edf(x, y, prec);
		else // if (rb_num_negative_p(rb_num_real(x)))
			a = rb_num_uminus(ipow_edf(rb_num_abs(x), y, prec));
	}
	else if (rb_num_real_p(y))
	{
		a = rb_bigmath_log(rb_num_abs(x), prec);
		a = rb_funcall1(y, '*', a);
		a = rb_bigmath_exp(a, prec);
		if (rb_num_negative_p(x))
			a = rb_num_uminus(a);
	}
	else
		rb_raise(rb_eTypeError, "not a Real");

	return a;
}
