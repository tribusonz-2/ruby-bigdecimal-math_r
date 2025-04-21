VALUE
sin_eulerf(VALUE z, VALUE prec)
{
	const ID sin = rb_intern("sin");
	z = rb_num_canonicalize(z, prec, ARG_REAL, ARG_RAWVALUE);
	z = trig_f_euler(sin, rb_ImaginaryZ(z, SIGN_PLUS), prec);
	return rb_num_real(z);
}
