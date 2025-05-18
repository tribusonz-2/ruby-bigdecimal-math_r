VALUE
log2_edf(VALUE x, VALUE prec)
{
	VALUE y = Qundef;

	rb_check_precise(prec);

	y = logxt_edf(x, INT2FIX(2), prec);

	return rb_num_round(y, prec);
}
