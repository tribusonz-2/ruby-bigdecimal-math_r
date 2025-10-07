static VALUE
csqrt_term(VALUE abs, VALUE a, VALUE prec, ID ops)
{
	const ID div = rb_intern("div");
	const ID round = rb_intern("round");
	VALUE t;
	t = rb_funcall(abs, ops, 2, a, prec);
	t = rb_funcall(t, div, 2, INT2FIX(2), prec);
	if (rb_num_negative_p(t))
		return BIG_ZERO;
	t = rb_bigmath_sqrt(t, prec);
	t = rb_funcall(t, round, 1, prec);
	return t;
}

VALUE
csqrt_formula(VALUE z, VALUE prec)
{
	const ID add = rb_intern("add"), sub = rb_intern("sub");
	VALUE w = Qundef, abs, re, im, sgn, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	abs = rb_bigmath_cabs(z, n);
	re = csqrt_term(abs, rb_num_real(z), n, add);
	im = csqrt_term(abs, rb_num_real(z), n, sub);
	sgn = rb_num_cmpeql(rb_num_imag(z), INT2NUM(0));

	if (rb_num_nonzero_p(sgn))
		w = rb_Complex(re, rb_num_coerce_bin(sgn, im, '*'));
	else
		w = rb_Complex(re, im);

	return rb_num_round(w, prec);
}
