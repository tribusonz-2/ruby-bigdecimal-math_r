VALUE
rb_bigmath_const_euler_gamma(VALUE prec)
{
	return rb_bigmath_const(BIGMATH_EulerGamma, EulerGamma_borwein_bailey, prec);
}
