VALUE
rb_bigmath_clog(VALUE z, VALUE prec)
{
	return clog_branch(z, prec, clog_formula);
}
