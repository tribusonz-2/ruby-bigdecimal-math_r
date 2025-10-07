VALUE
casec_logrep(VALUE z, VALUE prec)
{
	VALUE w, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	w = rb_funcall1(z, '*', z);
	w = rb_funcall1(BIG_ONE, '/', w);
	w = rb_funcall1(BIG_ONE, '-', w);
	w = rb_bigmath_csqrt(w, n);
	w = rb_funcall1(rb_ImaginaryZ(w, SIGN_PLUS), '+', 
		rb_num_canonicalize(z, n, ARG_COMPLEX, ARG_RECIPROCAL));
	w = rb_bigmath_clog(w, n);
	w = rb_ImaginaryZ(w, SIGN_MINUS);

	return rb_num_round(w, prec);
}
