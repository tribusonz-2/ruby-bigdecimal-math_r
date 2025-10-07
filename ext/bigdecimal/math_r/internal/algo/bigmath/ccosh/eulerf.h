VALUE
ccosh_eulerf(VALUE z, VALUE prec)
{
	VALUE w, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	w = trig_f_euler(mf_cos, z, n);

	return rb_num_round(w, prec);
}
