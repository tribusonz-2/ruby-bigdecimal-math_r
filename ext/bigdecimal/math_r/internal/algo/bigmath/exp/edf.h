VALUE
exp_edf(VALUE x, VALUE prec)
{
	const ID mult = rb_intern("mult");
	VALUE exp = Qundef, fra = Qundef;
	if (rb_num_notequal_p(x, x))
		return BIG_NAN;
	rb_bigmath_escalb(rb_bigmath_const_e(prec), x, prec, &exp, &fra);
	if (exp == Qundef || fra == Qundef)
		rb_raise(rb_eRuntimeError, "no solution");
	if (rb_num_infinite_p(exp) ||
	    rb_num_zero_p(exp) ||
	    rb_num_zero_p(fra))
		return rb_num_round(exp, prec);
	fra = rb_bigmath_expxt(fra, BIG_ONE, prec);
	if (CLASS_OF(exp) != rb_cBigDecimal)
		exp = rb_num_canonicalize(exp, prec, ARG_REAL, ARG_RAWVALUE);
	return rb_funcall(exp, mult, 2, fra, prec);
}
