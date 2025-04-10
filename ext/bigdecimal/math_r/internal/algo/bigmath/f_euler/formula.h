VALUE
f_euler_formula(VALUE theta, VALUE prec)
{
	VALUE sin, cos;
	rb_bigmath_sincos(theta, prec, &sin, &cos);
	return rb_Complex(cos, sin);
}
