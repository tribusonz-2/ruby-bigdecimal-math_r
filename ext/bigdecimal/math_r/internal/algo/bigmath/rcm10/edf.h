/**
 * Entity of rcm10(). It is equivalent to the following Ruby code:
 * 
 * ```ruby
 * def rcm10(x)
 *   reso = 0
 *   fra = x
 *   if x.finite? and x.nonzero?
 *     fra = Rational(fra.abs)
 *     has_sign = x < 0
 *     case
 *     when fra >= 10
 *       while fra >= 10
 *         reso += 1
 *         fra /= 10
 *       end
 *     when fra < 1
 *       while fra < 1
 *         reso -= 1
 *         fra *= 10
 *       end
 *     end
 *     fra = -fra if has_sign
 *   end
 *   [fra, reso]
 * end
 * ```
 */
VALUE
rcm10_edf(VALUE x, VALUE *reso)
{
	VALUE fra = x; *reso = INT2FIX(0);
	if (rb_num_nonzero_p(fra) && rb_num_finite_p(fra))
	{
		long resov = 0;
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
				resov++;
			}
		}
		else if (RTEST(rb_num_coerce_cmp(fra, INT2FIX(1), '<')))
		{
			while (RTEST(rb_num_coerce_cmp(fra, INT2FIX(1), '<')))
			{
				fra = rb_funcall1(fra, '*', rat_ten);
				resov--;
			}
		}
		if (has_sign)
			fra = rb_num_uminus(fra);
		*reso = LONG2FIX(resov);
	}
	return fra;
}
