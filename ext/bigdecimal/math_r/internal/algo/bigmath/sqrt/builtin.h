VALUE
sqrt_builtin(VALUE x, VALUE prec)
{
	const ID sqrt = rb_intern("sqrt");

	rb_check_precise(prec);

	if (rb_num_negative_p(x) || rb_num_nan_p(x))
		return BIG_NAN;

	return rb_num_round(rb_funcall(x, sqrt, 1, prec), prec);
}
