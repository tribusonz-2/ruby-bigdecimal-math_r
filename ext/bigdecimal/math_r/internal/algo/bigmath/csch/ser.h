VALUE
csch_ser(VALUE x, VALUE prec)
{
	VALUE y = Qundef;

	rb_check_precise(prec);

	sinhcosh_ser(x, prec, &y, NULL);

	return rb_num_canonicalize(y, prec, ARG_REAL, ARG_RECIPROCAL);
}
