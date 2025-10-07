VALUE
sech_eulerf(VALUE x, VALUE prec)
{
	VALUE y = Qundef, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	y = trig_f_euler(mf_cos, x, n);
	y = rb_num_canonicalize(y, n, ARG_REAL, ARG_RECIPROCAL);

	return rb_num_round(y, prec);
}
