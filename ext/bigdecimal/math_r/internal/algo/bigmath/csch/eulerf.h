VALUE
csch_eulerf(VALUE x, VALUE prec)
{
	VALUE y;

	rb_check_precise(prec);

	y = rb_ImaginaryZ(trig_f_euler(mf_sin, x, prec), SIGN_PLUS);

	return rb_num_canonicalize(y, prec, ARG_REAL, ARG_RECIPROCAL);
}
