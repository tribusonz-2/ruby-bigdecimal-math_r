VALUE
exp_builtin(VALUE x, VALUE prec)
{
	VALUE y, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	y = rb_funcall(rb_mBigMath, mf_exp, 2, x, n);

	return rb_num_round(y, prec);
}
