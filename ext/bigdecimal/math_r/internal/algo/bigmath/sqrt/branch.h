VALUE
sqrt_branch(VALUE x, VALUE prec, bigmath_func1 sqrt_cb)
{
#define SWITCH_PRECISION_NUMBER 2253
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (rb_num_negative_p(x))
		return BIG_NAN;
	else if (!rb_num_finite_p(x))
		return rb_BigDecimal1(x);
	if (TYPE(prec) == T_FIXNUM &&
	    NUM2LONG(prec) < SWITCH_PRECISION_NUMBER)
		return sqrt_builtin(x, prec);
	else
		return sqrt_cb(x, prec);
#undef SWITCH_PRECISION_NUMBER
}
