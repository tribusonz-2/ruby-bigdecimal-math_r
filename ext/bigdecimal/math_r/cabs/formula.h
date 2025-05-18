VALUE
cabs_formula(VALUE z, VALUE prec)
{
	rb_check_precise(prec);

	return rb_bigmath_l2norm(
		rb_assoc_new(rb_num_real(z), rb_num_imag(z)), prec);
}
