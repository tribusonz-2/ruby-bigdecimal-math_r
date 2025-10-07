VALUE
tanh_eulerf(VALUE x, VALUE prec)
{
	VALUE y = Qundef, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	y = rb_ImaginaryZ(trig_f_euler(mf_tan, x, n), SIGN_PLUS);
	y = rb_num_real(y);

	return rb_num_round(y, prec);
}
