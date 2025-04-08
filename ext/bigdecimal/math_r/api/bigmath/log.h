VALUE
rb_bigmath_log(VALUE x, VALUE prec)
{
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return log_branch(x, prec, log_edf);
}
