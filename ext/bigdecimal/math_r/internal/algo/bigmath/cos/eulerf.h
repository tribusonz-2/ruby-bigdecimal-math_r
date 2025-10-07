VALUE
cos_eulerf(VALUE z, VALUE prec)
{
	VALUE w, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	w = trig_f_euler(mf_cos, rb_ImaginaryZ(z, SIGN_PLUS), n);
	w = rb_num_real(w);
	
	return rb_num_round(w, prec);
}
