VALUE
cexp_eulerf(VALUE z, VALUE prec)
{
	const ID mult = rb_intern("mult");
	VALUE theta, r;

	rb_check_precise(prec);

	if (!rb_num_finite_p(rb_num_imag(z)))
		return rb_Complex(BIG_NAN, BIG_NAN);
	r = rb_num_canonicalize(rb_num_real(z), prec, ARG_REAL, ARG_RAWVALUE);
	r = rb_bigmath_exp(r, prec);
	if (rb_num_notequal_p(r, r))
		return rb_Complex(BIG_NAN, BIG_NAN);
	theta = f_euler_formula(rb_num_imag(z), prec);

	return rb_Complex(
		rb_funcall(rb_BigDecimal1(r), mult, 2, rb_num_real(theta), prec),
		rb_funcall(rb_BigDecimal1(r), mult, 2, rb_num_imag(theta), prec)
	);
}
