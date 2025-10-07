VALUE
sqrt_edom(VALUE x, VALUE prec)
{
	VALUE imag;
	RUBY_ASSERT(rb_num_negative_p(x));
	x = rb_num_uminus(x);
	imag = rb_bigmath_sqrt(x, prec);

	return rb_num_round(rb_Complex(BIG_ZERO, imag), prec);
}
