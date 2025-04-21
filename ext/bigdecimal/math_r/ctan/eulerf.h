VALUE
ctan_eulerf(VALUE z, VALUE prec)
{
	const ID tan = rb_intern("tan");
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return trig_f_euler(tan, rb_ImaginaryZ(z, SIGN_PLUS), prec);
}
