VALUE
log_builtin(VALUE x, VALUE prec)
{
	const ID log = rb_intern("log");
	VALUE y;

	rb_check_precise(prec);

	y = rb_funcall(rb_mBigMath, log, 2, x, prec);

	return rb_num_round(y, prec);
}
