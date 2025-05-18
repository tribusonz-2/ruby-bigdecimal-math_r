VALUE
asec_branch(VALUE x, VALUE prec, bigmath_func1 asec_cb)
{
	const ID leq = rb_intern("<=");
	const ID geq = rb_intern(">=");
	const ID div = rb_intern("div");
	VALUE y = Qundef;

	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);

	if (rb_num_nan_p(x))
		y = BIG_NAN;
	else if (rb_num_infinite_p(x) != 0)
		y = rb_funcall(rb_bigmath_const_pi(prec), div, 2, INT2FIX(2), prec);
	else if (RTEST(rb_num_coerce_bin(x, INT2FIX(-1), leq)) ||
	         RTEST(rb_num_coerce_bin(x, INT2FIX(1), geq)))
		y = asec_cb(x, prec);
	else
		y = BIG_NAN;

	return y;
}
