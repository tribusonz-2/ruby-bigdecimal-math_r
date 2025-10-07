void
escalb_edf(VALUE a, VALUE x, VALUE prec, VALUE *exp, VALUE *fra)
{
	const ID fix = rb_intern("fix");
	const ID frac = rb_intern("frac");
	const ID floor = rb_intern("floor");
	const ID pred = rb_intern("pred");
	const ID MAX_10_EXP = rb_intern("MAX_10_EXP");
	VALUE max_10_exp = rb_const_get_at(rb_cFloat, MAX_10_EXP);

	rb_check_precise(prec);

	if (!rb_num_finite_p(a) && !rb_num_positive_p(a))
		rb_raise(rb_eRangeError, "parameter a must be positive finite");
	switch (TYPE(x)) {
	case T_FIXNUM:
	case T_BIGNUM:
		*exp = x; *fra = BIG_ZERO;
		break;
	case T_FLOAT:
		if (isinf(NUM2DBL(x)) || isnan(NUM2DBL(x)))
		{
			*exp = rb_BigDecimal_flo(x); *fra = BIG_ZERO;
		}
		else
		{
			*exp = rb_funcall(x, floor, 0);
			*fra = rb_BigDecimal_flo(rb_funcall1(x, '%', INT2FIX(1)));
		}
		break;
	case T_RATIONAL:
		*exp = rb_funcall(x, floor, 0);
		*fra = rb_BigDecimal(rb_funcall1(x, '%', INT2FIX(1)), prec);
		break;
	case T_COMPLEX:
		rb_raise(rb_eTypeError, "no solution for Complex");
		break;
	default:
		if (rb_class_superclass(CLASS_OF(x)) == rb_cNumeric)
		{
			if (CLASS_OF(x) == rb_cBigDecimal)
			{
				if (!rb_num_finite_p(x))
				{
					*exp = x; *fra = BIG_ZERO;
				}
				else
				{
					*exp = rb_Integer(rb_funcall(x, fix, 0));
					if (rb_num_negative_p(x) &&
					    rb_num_notequal_p(*exp, x))
						*exp = rb_funcall(*exp, pred, 0);
					if (rb_num_notequal_p(*exp, x))
					{
						*fra = rb_funcall(x, frac, 0);
						if (rb_num_negative_p(*fra))
							*fra = rb_funcall1(BIG_ONE, '+', *fra);
					}
					else
						*fra = BIG_ZERO;
				}
			}
			else
				rb_raise(rb_eTypeError, "unknown numeric type");
		}
		rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
		break;
	}
	if (!rb_num_finite_p(x))
	{
		switch (rb_num_infinite_p(x)) {
		case 1:
			*exp = x;
			break;
		case -1:
			*exp = BIG_ZERO;
			break;
		default:
			*exp = BIG_NAN;
			break;
		}
		*fra = BIG_ZERO;
		return;
	}
	*exp = rb_bigmath_ipow(a, *exp,
		NUM2INT(rb_num_cmpeql(prec, max_10_exp)) == 1 ? prec : max_10_exp);
	*exp = rb_num_round(*exp,
		NUM2INT(rb_num_cmpeql(prec, max_10_exp)) == 1 ? prec : max_10_exp);
}
