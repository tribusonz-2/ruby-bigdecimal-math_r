VALUE
sin_eulerf(VALUE z, VALUE prec)
{
	const ID sin = rb_intern("sin");
	VALUE n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	z = trig_f_euler(sin, rb_ImaginaryZ(z, SIGN_PLUS), n);
	z = rb_num_real(z);

	return rb_num_round(z, prec);
}
