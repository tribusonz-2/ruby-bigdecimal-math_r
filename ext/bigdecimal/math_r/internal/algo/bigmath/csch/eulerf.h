VALUE
csch_eulerf(VALUE x, VALUE prec)
{
	VALUE y, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	y = rb_ImaginaryZ(trig_f_euler(mf_sin, x, n), SIGN_PLUS);
	y = rb_num_canonicalize(y, n, ARG_REAL, ARG_RECIPROCAL);

	return rb_num_round(y, prec);
}
