VALUE
log_edom(VALUE x, VALUE prec)
{
	VALUE y, pi = rb_bigmath_const_pi(prec);
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	RUBY_ASSERT (rb_num_negative_p(x));
	x = rb_num_uminus(x);
	y = rb_bigmath_log(x, prec);
	return rb_Complex(y, pi);
}
