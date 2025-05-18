VALUE
f_euler_formula(VALUE theta, VALUE prec)
{
	VALUE sin, cos;

	rb_check_precise(prec);

	rb_bigmath_sincos(theta, prec, &sin, &cos);

	return rb_Complex(cos, sin);
}
