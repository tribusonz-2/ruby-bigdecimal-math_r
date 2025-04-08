VALUE
log_builtin(VALUE x, VALUE prec)
{
	const ID log = rb_intern("log");
	if (rb_num_zero_p(x))
		return BIG_MINUS_INF;
	return rb_funcall(rb_mBigMath, log, 2, x, prec);
}

