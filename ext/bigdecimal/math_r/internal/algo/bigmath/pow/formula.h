VALUE
pow_formula(VALUE x, VALUE y, VALUE prec)
{
	VALUE a = Qundef, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	if (!rb_num_real_p(x))
		goto not_a_real_error;
	if (rb_num_zero_p(rb_num_real(x)))
		a = BIG_ONE;
	if (TYPE(y) == T_FIXNUM || TYPE(y) == T_BIGNUM)
	{
		if (rb_num_positive_p(rb_num_real(x)))
			a = ipow_edf(x, y, n);
		else // if (rb_num_negative_p(rb_num_real(x)))
			a = rb_num_uminus(ipow_edf(rb_num_abs(x), y, n));
	}
	else if (rb_num_real_p(y))
	{
		a = rb_bigmath_log(rb_num_abs(x), n);
		a = rb_funcall1(y, '*', a);
		a = rb_bigmath_exp(a, n);
		if (rb_num_negative_p(x))
			a = rb_num_uminus(a);
	}
	else
		goto not_a_real_error;

	return rb_num_round(a, prec);

not_a_real_error:
	rb_raise(rb_eTypeError, "not a Real");
}
