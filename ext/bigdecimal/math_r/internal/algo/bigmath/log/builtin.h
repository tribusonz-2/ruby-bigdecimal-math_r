VALUE
log_builtin(VALUE x, VALUE prec)
{
	const ID log = rb_intern("log");
	const ID add = rb_intern("add");
	VALUE exp, fra;
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	fra = rcm2_edf(x, &exp);
	exp = rb_funcall1(rb_bigmath_const_log2(prec), '*', exp);
	fra = rb_funcall(rb_mBigMath, log, 2, fra, prec);
	return rb_funcall(exp, add, 2, fra, prec);
}
