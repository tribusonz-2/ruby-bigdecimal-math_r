VALUE
log_edom(VALUE x, VALUE prec)
{
	VALUE y, pi = rb_bigmath_const_pi(prec), n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	x = rb_num_canonicalize(x, n, ARG_REAL, ARG_RAWVALUE);
	RUBY_ASSERT (rb_num_negative_p(x));
	x = rb_num_uminus(x);
	y = rb_bigmath_log(x, n);
	y = rb_Complex(y, pi);

	return rb_num_round(y, prec);
}
