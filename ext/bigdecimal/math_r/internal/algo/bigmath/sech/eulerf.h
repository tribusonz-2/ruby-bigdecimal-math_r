VALUE
sech_eulerf(VALUE x, VALUE prec)
{
	const ID cos = rb_intern("cos");
	VALUE y;
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	y = trig_f_euler(cos, x, prec);
	return rb_num_canonicalize(y, prec, ARG_REAL, ARG_RECIPROCAL);
}
