VALUE
log10_edf(VALUE x, VALUE prec)
{
	VALUE y = Qundef;

	rb_check_precise(prec);

	y = logxt_edf(x, INT2FIX(10), prec);

	return rb_num_round(y, prec);
}
