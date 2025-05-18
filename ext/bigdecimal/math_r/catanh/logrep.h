VALUE
catanh_logrep(VALUE z, VALUE prec)
{
	rb_check_precise(prec);

	z = rb_ImaginaryZ(z, SIGN_PLUS);
	z = catan_logrep(z, prec);

	return rb_ImaginaryZ(z, SIGN_MINUS);
}
