VALUE
ccbrt_formula(VALUE z, VALUE prec)
{
	VALUE one_third;

	rb_check_precise(prec);

	one_third = rb_Rational(INT2FIX(1), INT2FIX(3));

	return rb_bigmath_cpow(z, one_third, prec);
}
