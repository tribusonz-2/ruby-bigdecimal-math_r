VALUE
cabs_formula(VALUE z, VALUE prec)
{
	VALUE w, n;
	
	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	w = rb_bigmath_l2norm(
		rb_assoc_new(rb_num_real(z), rb_num_imag(z)), n);
	return rb_num_round(w, prec);
}
