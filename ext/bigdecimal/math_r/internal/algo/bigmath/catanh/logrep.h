VALUE
catanh_logrep(VALUE z, VALUE prec)
{
	VALUE n;
	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	z = rb_ImaginaryZ(z, SIGN_PLUS);
	z = catan_logrep(z, n);
	z = rb_ImaginaryZ(z, SIGN_MINUS);

	return rb_num_round(z, prec);
}
