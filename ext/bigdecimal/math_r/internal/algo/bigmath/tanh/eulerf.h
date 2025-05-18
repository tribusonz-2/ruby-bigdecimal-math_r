VALUE
tanh_eulerf(VALUE x, VALUE prec)
{
	VALUE y;

	rb_check_precise(prec);

	y = rb_ImaginaryZ(trig_f_euler(mf_tan, x, prec), SIGN_PLUS);

	return rb_num_real(y);
}
