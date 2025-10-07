VALUE
log_builtin(VALUE x, VALUE prec)
{
	const ID log = rb_intern("log");
	VALUE y, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	y = rb_funcall(rb_mBigMath, log, 2, x, n);

	return rb_num_round(y, prec);
}
