VALUE
csin_eulerf(VALUE z, VALUE prec)
{
	VALUE w;

	rb_check_precise(prec);

	w = trig_f_euler(mf_sin, rb_ImaginaryZ(z, SIGN_PLUS), prec);

	return w;
}
