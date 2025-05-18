VALUE
LOG_PI_builtin(VALUE prec)
{
	VALUE log_pi = rb_bigmath_const_pi(prec);
	return log_builtin(log_pi, prec);
}

