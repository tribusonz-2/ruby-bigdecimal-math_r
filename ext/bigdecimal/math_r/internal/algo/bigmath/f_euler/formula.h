VALUE
f_euler_formula(VALUE theta, VALUE prec)
{
	VALUE sin, cos, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	rb_bigmath_sincos(theta, n, &sin, &cos);

	return rb_Complex(cos, sin);
}
