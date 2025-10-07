VALUE
casech_logrep(VALUE z, VALUE prec)
{
	VALUE n;
	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	z = rb_num_canonicalize(z, n, ARG_COMPLEX, ARG_RECIPROCAL);

	return cacosh_logrep(z, prec);
}
