VALUE
cacsch_logrep(VALUE z, VALUE prec)
{
	rb_check_precise(prec);

	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	z = rb_ImaginaryZ(z, SIGN_PLUS);
	z = cacsc_logrep(z, prec);

	return rb_ImaginaryZ(z, SIGN_PLUS);
}
