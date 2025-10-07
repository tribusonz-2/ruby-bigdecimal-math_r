static inline void
f_euler2(VALUE theta, VALUE prec, VALUE *exppz, VALUE *expmz)
{
	const ID conj = rb_intern("conj");
	*exppz = f_euler_formula(rb_num_imag(theta), prec);
	*expmz = rb_funcall(*exppz, conj, 0);
}


static inline void
f_euler_e2(VALUE theta, VALUE prec, VALUE *exppz, VALUE *expmz)
{
	const ID div = rb_intern("div");
	VALUE r = rb_num_real(theta);
	r = rb_num_canonicalize(r, prec, ARG_REAL, ARG_RAWVALUE);
	r = rb_bigmath_exp(r, prec);
	if (rb_num_notequal_p(r, r))
	{
		*exppz = BIG_NAN;
		*expmz = BIG_NAN;
	}
	else if (TYPE(r) == T_FIXNUM || TYPE(r) == T_BIGNUM)
	{
		*exppz = rb_BigDecimal1(r);
		r = rb_Rational(INT2FIX(1), r);
		*expmz = rb_BigDecimal(r, prec);
	}
	else
	{
		*exppz = rb_BigDecimal1(r);
		r = rb_funcall(BIG_ONE, div, 2, r, prec);
		*expmz = rb_BigDecimal1(r);
	}
}


static inline VALUE
f_euler_cos(VALUE exppz, VALUE expmz)
{
	VALUE y = rb_funcall1(exppz, '+', expmz);
	y = rb_funcall1(y, '/', INT2FIX(2));
	if (rb_num_real_p(y))
		y = rb_Complex(y, BIG_ZERO);
	return y;
}

static inline VALUE
f_euler_sin_infinite(VALUE y)
{
	VALUE w = Qundef;
	int real_sign, imag_sign;
	real_sign = rb_num_infinite_p(rb_num_real(y));
	imag_sign = rb_num_infinite_p(rb_num_imag(y));
	if (real_sign == 1)
	{
		VALUE imag = rb_num_imag(y);
		if (rb_num_zero_p(imag))
			w = rb_Complex(BIG_ZERO, BIG_MINUS_INF);
		else if (rb_num_positive_p(imag))
			w = rb_Complex(BIG_MINUS_INF, BIG_INF);
		else if (rb_num_negative_p(imag))
			w = rb_Complex(BIG_INF, BIG_INF);
	}
	else if (real_sign == -1)
	{
		VALUE imag = rb_num_imag(y);
		if (rb_num_zero_p(imag))
			w = rb_Complex(BIG_ZERO, BIG_INF);
		else if (rb_num_positive_p(imag))
			w = rb_Complex(BIG_INF, BIG_INF);
		else if (rb_num_negative_p(imag))
			w = rb_Complex(BIG_MINUS_INF, BIG_INF);
	}
	else if (imag_sign == 1)
	{
		VALUE real = rb_num_real(y);
		if (rb_num_zero_p(real))
			w = rb_Complex(BIG_INF, BIG_ZERO);
		else if (rb_num_positive_p(real))
			w = rb_Complex(BIG_MINUS_INF, BIG_INF);
		else if (rb_num_negative_p(real))
			w = rb_Complex(BIG_INF, BIG_INF);
	}
	else if (imag_sign == -1)
	{
		VALUE real = rb_num_real(y);
		if (rb_num_zero_p(real))
			w = rb_Complex(BIG_MINUS_INF, BIG_ZERO);
		else if (rb_num_positive_p(real))
			w = rb_Complex(BIG_MINUS_INF, BIG_MINUS_INF);
		else if (rb_num_negative_p(real))
			w = rb_Complex(BIG_MINUS_INF, BIG_INF);
	}

	if (w == Qundef)
		rb_raise(rb_eRuntimeError, "no solution (in f_euler_sin_infinite())");
	return w;
}

static inline VALUE
f_euler_sin(VALUE exppz, VALUE expmz)
{
	VALUE y = rb_funcall1(exppz, '-', expmz);
	VALUE two_i = rb_Complex(BIG_ZERO, rb_BigDecimal1(INT2FIX(2)));
	// BUG: In the current version 3.3.5
	// -Float::INFINITY / 2i #=> (NaN+Infinity*i)
	// Correct: (0.0+Infinity*i)
	if (!rb_num_finite_p(y))
		y = f_euler_sin_infinite(y);
	else
		y = rb_funcall1(y, '/', two_i);
	return y;
}

static inline VALUE
f_euler_tan(VALUE exppz, VALUE expmz)
{
	VALUE sin, cos;

	if (rb_num_zero_p(exppz))
		return rb_Complex(BIG_ZERO, BIG_ONE);
	else if (rb_num_infinite_p(exppz))
		return rb_Complex(BIG_ZERO, BIG_MINUS_ONE);
	/* else */
	sin = rb_funcall1(expmz, '-', exppz);
	sin = rb_ImaginaryZ(sin, SIGN_PLUS);
	cos = rb_funcall1(expmz, '+', exppz);
	return rb_funcall1(sin, '/', cos);
}

static inline VALUE
f_euler_sc(const ID func, VALUE theta, VALUE prec)
{
	VALUE exppz = Qundef, expmz = Qundef, y = Qundef;

	if (!rb_num_finite_p(rb_num_imag(theta)))
		return rb_Complex(BIG_NAN, BIG_NAN);

	f_euler2(theta, prec, &exppz, &expmz);

	if (func == mf_cos)
	{
		y = f_euler_cos(exppz, expmz);
	}
	else if (func == mf_sin)
	{
		y = f_euler_sin(exppz, expmz);
	}
	else if (func == mf_tan)
	{
		y = f_euler_tan(exppz, expmz);
	}
	return rb_num_round(y, prec);
}

// For real of tangent's exponent, tanh(x), coth(x) or tan(i x) or cot(i x)
static inline VALUE
f_euler_t(VALUE theta, VALUE prec)
{
	const ID div = rb_intern("div");
	const ID sub = rb_intern("sub");
	const ID add = rb_intern("add");
	const ID pred = rb_intern("pred");
	const ID succ = rb_intern("succ");
	VALUE y = Qundef;
	theta = rb_num_real(theta);
	theta = rb_num_canonicalize(theta, prec, ARG_REAL, ARG_RAWVALUE);
	if (!rb_num_finite_p(theta))
	{
		switch (NUM2INT(rb_BigDecimal_sign(theta))) {
		case 0:
			y = BIG_NAN;
			break;
		case 3:
			y = BIG_ONE;
			break;
		case -3:
			y = BIG_MINUS_ONE;
			break;
		}
	}
	else
	{
		y = rb_bigmath_exp(rb_funcall(INT2FIX(2), '*', 1, rb_num_real(theta)), prec);
		if (CLASS_OF(y) == rb_cBigDecimal)
		{
			if (rb_num_finite_p(y))
				y = rb_funcall(
					rb_funcall(y, sub, 2, INT2FIX(1), prec), div, 2,
					rb_funcall(y, add, 2, INT2FIX(1), prec), prec
				    );
			else if (rb_num_infinite_p(y))
				y = BIG_ONE;
		}
		else if (TYPE(y) == T_FIXNUM || TYPE(y) == T_BIGNUM)
		{
			y = rb_BigDecimal(
				rb_Rational(
					rb_funcall(y, pred, 0),
					rb_funcall(y, succ, 0)
				), prec);
		}
		else
			y = BIG_ONE;
	}
	if (y == Qundef)
		rb_raise(rb_eRuntimeError, "no solution");
	return rb_ImaginaryZ(y, SIGN_MINUS);
}


static inline VALUE
f_euler_h(const ID func, VALUE theta, VALUE prec)
{
	VALUE y = Qundef, exppz = Qundef, expmz = Qundef;

	if (func == mf_tan)
		return f_euler_t(theta, prec);

	f_euler_e2(rb_num_real(theta), prec, &exppz, &expmz);

	if (func == mf_cos)
	{
		y = f_euler_cos(exppz, expmz);
	}
	else if (func == mf_sin)
	{
		y = f_euler_sin(exppz, expmz);
	}
	return rb_num_round(y, prec);
}

static inline VALUE
f_euler_esc(const ID func, VALUE z, VALUE prec)
{
	VALUE e_exppz  = Qundef,
	      e_expmz  = Qundef,
	      sc_exppz = Qundef,
	      sc_expmz = Qundef,
	      exppz    = Qundef,
	      expmz    = Qundef,
	      y        = Qundef;
	f_euler_e2(z, prec, &e_exppz, &e_expmz);
	f_euler2(z, prec, &sc_exppz, &sc_expmz);
	exppz = rb_funcall1(e_exppz, '*', sc_exppz);
	expmz = rb_funcall1(e_expmz, '*', sc_expmz);

	if (func == mf_cos)
	{
		y = f_euler_cos(exppz, expmz);
	}
	else if (func == mf_sin)
	{
		y = f_euler_sin(exppz, expmz);
	}
	else if (func == mf_tan)
	{
		y = f_euler_tan(exppz, expmz);
	}
	return rb_num_round(y, prec);
}

VALUE
trig_f_euler(const ID func, VALUE theta, VALUE prec)
{
	VALUE h = Qundef, sc = Qundef;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	if (rb_num_nan_p(theta))
		return rb_Complex(BIG_NAN, BIG_NAN);
	if (rb_num_zero_p(rb_num_imag(theta)))
	{
		h = f_euler_h(func, theta, n);
		h = rb_num_round(h, prec);
		if (rb_num_nan_p(h))
			return h;
	}
	if (rb_num_zero_p(rb_num_real(theta)))
	{
		sc = f_euler_sc(func, theta, n);
		sc = rb_num_round(sc, prec);
		if (rb_num_nan_p(sc))
			return sc;
	}
	if (h != Qundef && sc == Qundef)
		return h;
	else if (h == Qundef && sc != Qundef)
		return sc;
	else
	{
		VALUE y = f_euler_esc(func, theta, n);
		return rb_num_round(y, prec);
	}
}
