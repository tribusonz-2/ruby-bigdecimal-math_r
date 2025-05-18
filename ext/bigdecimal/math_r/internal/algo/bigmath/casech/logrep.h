VALUE
casech_logrep(VALUE z, VALUE prec)
{
	rb_check_precise(prec);

	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RECIPROCAL);

	return cacosh_logrep(z, prec);
}
