static VALUE
canonicalize_decimalize(VALUE x, VALUE prec)
{
	switch (TYPE(x)) {
	case T_FIXNUM:
	case T_BIGNUM:
		x = rb_BigDecimal1(x);
		break;
	case T_FLOAT:
		x = rb_BigDecimal_flo(x);
		break;
	case T_RATIONAL:
		x = rb_BigDecimal(x, prec);
		break;
	default:
		break;
	}
	return x;
}

static inline VALUE
canonicalize_iter(RB_BLOCK_CALL_FUNC_ARGLIST(val, _))
{
	const ID abs2 = rb_intern("abs2");
	return rb_funcall(val, abs2, 0);
}

VALUE
rb_num_canonicalize(VALUE x, VALUE prec, bool complex_form, bool inversion)
{
	const ID sum = rb_intern("sum");
	const ID div = rb_intern("div");
retry:
	switch (TYPE(x)) {
	case T_FIXNUM:
	case T_BIGNUM:
		if (inversion)
			{ x = rb_Rational(INT2FIX(1), x); x = rb_BigDecimal(x, prec); }
		else
			x = rb_BigDecimal1(x);
		if (complex_form)
			x = rb_Complex(x, BIG_ZERO);
		break;
	case T_FLOAT:
		if (inversion)
			x = DBL2NUM(1 / NUM2DBL(x));
		x = rb_BigDecimal_flo(x);
		if (complex_form)
			x = rb_Complex(x, BIG_ZERO);
		break;
	case T_RATIONAL:
		if (inversion)
			x = rb_funcall1(INT2FIX(1), '/', x);
		x = rb_BigDecimal(x, prec);
		if (complex_form)
			x = rb_Complex(x, BIG_ZERO);
		break;
	case T_COMPLEX:
		if (rb_num_zero_p(x))
		{
			x = rb_num_real(x);
			goto retry;
		}
		else if (!complex_form && rb_num_nonzero_p(rb_num_imag(x)))
			rb_raise(rb_eTypeError, "not a Real");
		else if (
		    (!complex_form &&
		      rb_num_zero_p(rb_num_imag(x))) ||
		     (complex_form &&
		      rb_num_infinite_p(rb_num_real(x)) &&
		      rb_num_finite_p(rb_num_imag(x))))
		{
			x = rb_num_real(x);
			goto retry;
		}
		else if (complex_form && rb_num_infinite_p(rb_num_imag(x)))
		{
			if (rb_num_finite_p(rb_num_real(x)))
				x = rb_Complex(BIG_ZERO, BIG_ZERO);
			else
				x = rb_Complex(BIG_NAN, BIG_NAN);
		}
		else if (complex_form)
		{
			VALUE norm, real, imag;
			real = canonicalize_decimalize(rb_num_real(x), prec);
			imag = canonicalize_decimalize(rb_num_imag(x), prec);
			if (inversion)
			{
				norm = rb_block_call(
					rb_assoc_new(
					  rb_num_real(x), 
					  rb_num_imag(x)), 
					sum, 0, NULL,
					canonicalize_iter, prec);
				real = rb_funcall(real, div, 2, norm, prec);
				imag = rb_funcall(imag, div, 2, norm, prec);
				x = rb_Complex(real, rb_num_uminus(imag));
			}
			else
			{
				x = rb_Complex(real, imag);
			}
		}
		else
			x = rb_Complex(BIG_NAN, BIG_NAN);
		break;
	case T_NIL: case T_TRUE: case T_FALSE:
		rb_raise(rb_eTypeError,
			"can't convert %"PRIsVALUE" into Numeric", rb_inspect(x));
		break;
	default:
		if (rb_class_superclass(CLASS_OF(x)) != rb_cNumeric)
			rb_raise(rb_eTypeError,
				"can't convert %"PRIsVALUE" into Numeric", CLASS_OF(x));
		else if (CLASS_OF(x) == rb_cBigDecimal)
		{
			if (inversion)
				x = rb_funcall(BIG_ONE, div, 2, x, prec);
			if (complex_form)
				x = rb_Complex(x, BIG_ZERO);
		}
		break;
	}
	if (complex_form && rb_num_real_p(x))
		x = rb_Complex(x, BIG_ZERO);
	return x;
}
