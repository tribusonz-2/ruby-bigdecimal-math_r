VALUE
cot_eulerf(VALUE z, VALUE prec)
{
	VALUE w;

	rb_check_precise(prec);

	w = trig_f_euler(mf_tan, rb_ImaginaryZ(z, SIGN_PLUS), prec);

	return rb_num_canonicalize(w, prec, ARG_REAL, ARG_RECIPROCAL);
}
