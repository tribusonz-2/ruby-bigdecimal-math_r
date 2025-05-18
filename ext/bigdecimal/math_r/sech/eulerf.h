VALUE
sech_eulerf(VALUE x, VALUE prec)
{
	VALUE y;

	rb_check_precise(prec);

	y = trig_f_euler(mf_cos, x, prec);

	return rb_num_canonicalize(y, prec, ARG_REAL, ARG_RECIPROCAL);
}
