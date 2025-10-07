VALUE
csin_eulerf(VALUE z, VALUE prec)
{
	VALUE w, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	w = trig_f_euler(mf_sin, rb_ImaginaryZ(z, SIGN_PLUS), n);

	return rb_num_round(w, prec);
}
