VALUE
ccsch_eulerf(VALUE z, VALUE prec)
{
	VALUE w, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	w = rb_ImaginaryZ(trig_f_euler(mf_sin, z, n), SIGN_PLUS);
	w = rb_num_canonicalize(w, n, ARG_COMPLEX, ARG_RECIPROCAL);

	return rb_num_round(w, prec);
}
