VALUE
ctanh_eulerf(VALUE z, VALUE prec)
{
	VALUE w, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	w = rb_ImaginaryZ(trig_f_euler(mf_tan, z, n), SIGN_PLUS);

	return rb_num_round(w, prec);
}
