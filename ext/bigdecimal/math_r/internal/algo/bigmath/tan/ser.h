VALUE
tan_ser(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE sin, cos;

	rb_check_precise(prec);

	if (!rb_num_finite_p(x))
		return BIG_NAN;
	rb_check_precise(prec);
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	rb_bigmath_sincos(x, prec, &sin, &cos);
	sin = rb_num_round(sin, prec);
	cos = rb_num_round(cos, prec);

	return rb_funcall(sin, div, 2, cos, prec);
}
