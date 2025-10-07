VALUE
ccbrt_formula(VALUE z, VALUE prec)
{
	VALUE one_third, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	one_third = rb_Rational(INT2FIX(1), INT2FIX(3));

	z = rb_bigmath_cpow(z, one_third, n);
	
	return rb_num_round(z, prec);
}
