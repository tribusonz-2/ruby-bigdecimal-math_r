VALUE
ccosh_eulerf(VALUE z, VALUE prec)
{
	const ID cos = rb_intern("cos");
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return trig_f_euler(cos, z, prec);
}
