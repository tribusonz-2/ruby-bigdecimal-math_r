VALUE
sqrt_builtin(VALUE x, VALUE prec)
{
	const ID sqrt = rb_intern("sqrt");
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	if (rb_num_negative_p(x) || rb_num_notequal_p(x, x))
		return BIG_NAN;
	return rb_funcall(x, sqrt, 1, prec);
}
