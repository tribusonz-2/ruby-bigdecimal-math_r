VALUE
ccosh_eulerf(VALUE z, VALUE prec)
{
	VALUE w;

	rb_check_precise(prec);

	w = trig_f_euler(mf_cos, z, prec);

	return w;
}
