VALUE
csech_eulerf(VALUE z, VALUE prec)
{
	VALUE w, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	w = trig_f_euler(mf_cos, z, n);
	w = rb_num_canonicalize(w, n, ARG_COMPLEX, ARG_RECIPROCAL);

	return rb_num_round(w, prec);
}
