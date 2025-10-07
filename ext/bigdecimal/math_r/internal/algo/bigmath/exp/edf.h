VALUE
exp_edf(VALUE x, VALUE prec)
{
	const ID mult = rb_intern("mult");
	VALUE exp = Qundef, fra = Qundef, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	if (rb_num_notequal_p(x, x))
		return BIG_NAN;
	rb_bigmath_escalb(rb_bigmath_const_e(n), x, n, &exp, &fra);
	if (exp == Qundef || fra == Qundef)
		rb_raise(rb_eRuntimeError, "no solution");
	if (rb_num_infinite_p(exp) ||
	    rb_num_zero_p(exp) ||
	    rb_num_zero_p(fra))
		return rb_num_round(exp, n);
	fra = rb_bigmath_expxt(fra, BIG_ONE, n);
	if (CLASS_OF(exp) != rb_cBigDecimal)
		exp = rb_num_canonicalize(exp, n, ARG_REAL, ARG_RAWVALUE);

	return rb_funcall(exp, mult, 2, fra, prec);
}
