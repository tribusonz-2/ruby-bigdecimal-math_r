VALUE
exp2_branch(VALUE x, VALUE prec, bigmath_func1 exp2_cb)
{
	const ID mult = rb_intern("mult");
	VALUE w = Qundef;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (rb_num_nan_p(x))
		w = BIG_NAN;
	else
	{
	        VALUE exp = Qundef, fra = Qundef;
		rb_bigmath_escalb(
			rb_BigDecimal1(INT2FIX(2)), x, prec, &exp, &fra);
		if (exp == Qundef || fra == Qundef)
			rb_raise(rb_eRuntimeError, "no solution");
		else if (rb_num_infinite_p(exp) || rb_num_zero_p(exp) || rb_num_zero_p(fra))
			w = rb_num_round(exp, prec);
		else
		{
			fra = exp2_cb(fra, prec);
			if (CLASS_OF(exp) != rb_cBigDecimal)
				exp = rb_num_canonicalize(exp, prec, ARG_REAL, ARG_RAWVALUE);
			w = rb_funcall(exp, mult, 2, fra, prec);
		}
	}
	return w;
}
