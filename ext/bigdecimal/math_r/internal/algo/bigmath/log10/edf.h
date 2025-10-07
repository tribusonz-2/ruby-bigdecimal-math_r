VALUE
log10_edf(VALUE x, VALUE prec)
{
	VALUE y = Qundef, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	y = logxt_edf(x, INT2FIX(10), n);

	return rb_num_round(y, prec);
}
