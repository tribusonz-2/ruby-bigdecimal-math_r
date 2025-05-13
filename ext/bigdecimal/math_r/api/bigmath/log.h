

VALUE
rb_bigmath_log(VALUE x, VALUE prec)
{
	return log_branch(x, prec, log_builtin);
}
