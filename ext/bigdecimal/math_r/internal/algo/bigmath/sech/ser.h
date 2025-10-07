VALUE
sech_ser(VALUE x, VALUE prec)
{
	VALUE y = Qundef, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	sinhcosh_ser(x, n, NULL, &y);
	y = rb_num_canonicalize(y, n, ARG_REAL, ARG_RECIPROCAL);

	return rb_num_round(y, prec);
}
