VALUE
log_builtin(VALUE x, VALUE prec)
{
	const ID log = rb_intern("log");
	if (rb_num_zero_p(x))
		return BIG_MINUS_INF;

	VALUE exp, fra;
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	fra = rcm2_edf(x, &exp);
	fra = rb_funcall(rb_mBigMath, log, 2, fra, prec);
	return rb_num_round(rb_funcall(exp, '+', fra), prec);
}

