VALUE
cos_eulerf(VALUE z, VALUE prec)
{
	VALUE w;

	rb_check_precise(prec);

	w = trig_f_euler(mf_cos, rb_ImaginaryZ(z, SIGN_PLUS), prec);

	return rb_num_real(w);
}
