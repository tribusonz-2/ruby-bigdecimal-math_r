VALUE
csc_eulerf(VALUE z, VALUE prec)
{
	VALUE w, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	w = trig_f_euler(mf_sin, rb_ImaginaryZ(z, SIGN_PLUS), prec);
	w = rb_num_canonicalize(w, n, ARG_REAL, ARG_RECIPROCAL);

	return rb_num_round(w, prec);
}
