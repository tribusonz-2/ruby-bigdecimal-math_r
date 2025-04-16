VALUE
csin_eulerf(VALUE z, VALUE prec)
{
	const ID sin = rb_intern("sin");
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return trig_f_euler(sin, rb_ImaginaryZ(z, SIGN_PLUS), prec);
}
