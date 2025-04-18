VALUE
clog_formula(VALUE z, VALUE prec)
{
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	VALUE real = rb_bigmath_log(rb_bigmath_cabs(z, prec), prec);
	VALUE imag = rb_bigmath_carg(z, prec);
	return rb_Complex(real, imag);
}
