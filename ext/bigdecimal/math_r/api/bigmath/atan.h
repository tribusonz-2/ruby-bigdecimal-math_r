
VALUE
rb_bigmath_atan(VALUE x, VALUE prec)
{
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	return atan_branch(x, prec, atan_ser_euler);
}
