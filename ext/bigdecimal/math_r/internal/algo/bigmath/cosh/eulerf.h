VALUE
cosh_eulerf(VALUE x, VALUE prec)
{
	VALUE y, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	y = trig_f_euler(mf_cos, x, n);
	y = rb_num_real(y);

	return rb_num_round(y, prec);
}
