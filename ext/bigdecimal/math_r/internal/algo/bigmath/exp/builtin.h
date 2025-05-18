VALUE
exp_builtin(VALUE x, VALUE prec)
{
	VALUE y = rb_funcall(rb_mBigMath, mf_exp, 2, x, prec);
	return rb_num_round(y, prec);
}
