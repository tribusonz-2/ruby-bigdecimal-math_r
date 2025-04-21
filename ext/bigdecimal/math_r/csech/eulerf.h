VALUE
csech_eulerf(VALUE z, VALUE prec)
{
	const ID cos = rb_intern("cos");
	VALUE w;
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	w = trig_f_euler(cos, z, prec);
	return rb_num_canonicalize(w, prec, ARG_COMPLEX, ARG_RECIPROCAL);
}
