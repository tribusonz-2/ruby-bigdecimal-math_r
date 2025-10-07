VALUE
carg_formula(VALUE z, VALUE prec)
{
	VALUE n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	z = rb_bigmath_quadrant(rb_num_real(z), rb_num_imag(z), n);
	
	return rb_num_round(z, prec);
}
