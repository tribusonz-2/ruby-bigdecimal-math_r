VALUE
cacoth_logrep(VALUE z, VALUE prec)
{
	VALUE n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	z = rb_num_canonicalize(z, n, ARG_COMPLEX, ARG_RAWVALUE);
	z = rb_ImaginaryZ(z, SIGN_MINUS);
	z = cacot_logrep(z, n);
	z = rb_ImaginaryZ(z, SIGN_MINUS);
	
	return rb_num_round(z, prec);
}
