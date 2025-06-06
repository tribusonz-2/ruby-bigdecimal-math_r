VALUE
rcm2_edf(VALUE x, VALUE *reso)
{
	VALUE fra = x; *reso = INT2FIX(0);
	if (rb_num_nonzero_p(fra) && rb_num_finite_p(fra))
	{
		long resov = 0;
		bool has_sign = RTEST(rb_num_coerce_cmp(x, INT2FIX(0), '<'));
		VALUE rat_two = rb_rational_new1(INT2FIX(2));
		fra = rb_Rational1(fra);
		if (rb_num_negative_p(fra))
			fra = rb_num_uminus(fra);
		if (RTEST(rb_num_coerce_cmp(fra, INT2FIX(1), rb_intern(">="))))
		{
			while (RTEST(rb_num_coerce_cmp(INT2FIX(2), fra, rb_intern("<="))))
			{
				fra = rb_funcall1(fra, '/', rat_two);
				resov++;
			}
		}
		else
		{
			while (RTEST(rb_num_coerce_cmp(INT2FIX(1), fra, '>')))
			{
				fra = rb_funcall1(fra, '*', rat_two);
				resov--;
			}
		}
		if (has_sign)
			fra = rb_num_uminus(fra);
		*reso = LONG2FIX(resov);
	}
	return fra;
}
