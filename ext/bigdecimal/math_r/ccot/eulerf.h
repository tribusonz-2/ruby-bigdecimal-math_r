VALUE
ccot_eulerf(VALUE z, VALUE prec)
{
	const ID tan = rb_intern("tan");
	VALUE w;
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	w = trig_f_euler(tan, rb_ImaginaryZ(z, SIGN_PLUS), prec);
	return rb_num_canonicalize(w, prec, ARG_COMPLEX, ARG_RECIPROCAL);
}
