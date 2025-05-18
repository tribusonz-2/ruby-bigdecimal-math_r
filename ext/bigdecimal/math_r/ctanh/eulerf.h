VALUE
ctanh_eulerf(VALUE z, VALUE prec)
{
	VALUE w;

	rb_check_precise(prec);

	w = rb_ImaginaryZ(trig_f_euler(mf_tan, z, prec), SIGN_PLUS);

	return w;
}
