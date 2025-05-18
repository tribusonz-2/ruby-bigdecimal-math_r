VALUE
rb_bigmath_const_log_pi(VALUE prec)
{
	return rb_bigmath_const(BIGMATH_LOG_PI, LOG_PI_builtin, prec);
}
