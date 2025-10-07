VALUE
rcm10_edf(VALUE x, VALUE *reso)
{
	VALUE fra = x; *reso = INT2FIX(0);
	if (rb_num_nonzero_p(fra) && rb_num_finite_p(fra))
	{
		const ID succ = rb_intern("succ");
		const ID pred = rb_intern("pred");
		VALUE resov = LONG2FIX(0);
		bool has_sign = RTEST(rb_num_coerce_cmp(x, INT2FIX(0), '<'));
		VALUE rat_ten = rb_rational_new1(INT2FIX(10));
		fra = rb_Rational1(fra);
		if (rb_num_negative_p(fra))
			fra = rb_num_uminus(fra);
		if (RTEST(rb_num_coerce_cmp(fra, INT2FIX(10), rb_intern(">="))))
		{
			while (RTEST(rb_num_coerce_cmp(fra, INT2FIX(10), rb_intern(">="))))
			{
				fra = rb_funcall1(fra, '/', rat_ten);
				resov = TYPE(resov) == T_FIXNUM ? 
					LONG2FIX(FIX2LONG(resov) + 1) : 
					rb_funcall(resov, succ, 0);
			}
		}
		else if (RTEST(rb_num_coerce_cmp(fra, INT2FIX(1), '<')))
		{
			while (RTEST(rb_num_coerce_cmp(fra, INT2FIX(1), '<')))
			{
				fra = rb_funcall1(fra, '*', rat_ten);
				resov = TYPE(resov) == T_FIXNUM ? 
					LONG2FIX(FIX2LONG(resov) - 1) : 
					rb_funcall(resov, pred, 0);
			}
		}
		if (has_sign)
			fra = rb_num_uminus(fra);
		*reso = resov;
	}
	return fra;
}
