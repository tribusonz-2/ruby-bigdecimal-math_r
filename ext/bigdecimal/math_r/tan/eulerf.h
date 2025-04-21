VALUE
tan_eulerf(VALUE z, VALUE prec)
{
	const ID tan = rb_intern("tan");
	z = rb_num_canonicalize(z, prec, ARG_REAL, ARG_RAWVALUE);
	z = trig_f_euler(tan, rb_ImaginaryZ(z, SIGN_PLUS), prec);
	return rb_num_real(z);
}
