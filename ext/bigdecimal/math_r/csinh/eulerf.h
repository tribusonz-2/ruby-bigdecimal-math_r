VALUE
csinh_eulerf(VALUE z, VALUE prec)
{
	const ID sin = rb_intern("sin");
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_ImaginaryZ(trig_f_euler(sin, z, prec), SIGN_PLUS);
}
