VALUE
LOG_PI_builtin(VALUE prec)
{
	rb_check_precise(prec);
	VALUE n = rb_numdiff_make_n(prec);
	VALUE log_pi = rb_bigmath_const_pi(n);
	return log_builtin(log_pi, prec);
}

