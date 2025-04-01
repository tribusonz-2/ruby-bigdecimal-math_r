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
rb_bigmath_csqrt(VALUE z, VALUE prec)
{
	VALUE w = Qundef;
	rb_check_precise(prec);
	if (!rb_num_finite_p(z))
	{
		int re_sgn, im_sgn;
		if ((re_sgn = rb_num_infinite_p(rb_num_real(z)) != 0) &&
		    (rb_num_infinite_p(rb_num_imag(z))) != 0)
		{
			switch (re_sgn) {
			case 1:
				w = rb_Complex1(BIG_INF);
				break;
			case -1:
				w = rb_Complex(BIG_ZERO, BIG_INF);
				break;
			}
		}
		else if ((im_sgn = rb_num_infinite_p(rb_num_imag(z))) != 0)
		{
			w = rb_Complex(
				BIG_INF,
				rb_num_coerce_bin(im_sgn, BIG_INF, '*')
			);
		}
		else
		{
			w = rb_Complex(BIG_NAN, BIG_NAN);
		}
	}
	else // if (rb_num_finite_p(z))
	{
		const ID add = rb_intern("add"), sub = rb_intern("sub");
		VALUE abs = rb_bigmath_cabs(z, prec),
		      re = csqrt_term(abs, rb_num_real(z), prec, add),
		      im = csqrt_term(abs, rb_num_real(z), prec, sub),
		      sgn = rb_num_cmpeql(rb_num_imag(z), INT2NUM(0));
		if (rb_num_nonzero_p(sgn))
			w = rb_Complex(re, rb_num_coerce_bin(sgn, im, '*'));
		else
			w = rb_Complex(re, im);
	}
	if (w == Qundef)
		rb_raise(rb_eRuntimeError, "no solution");
	return w;
}
