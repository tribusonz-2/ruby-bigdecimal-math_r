VALUE
cosh_ser(VALUE x, VALUE prec)
{
	VALUE y = Qundef, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	sinhcosh_ser(x, n, NULL, &y);

	return rb_num_round(y, prec);
}
