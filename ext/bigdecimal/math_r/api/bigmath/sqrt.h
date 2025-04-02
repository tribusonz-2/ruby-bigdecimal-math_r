
#define SWITCH_PRECISION_NUMBER 2253

// Reference: C-gengo ni yoru hyoujun algorithm jiten - Haruhiko Okumura
static VALUE
sqrt_newton(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE s = Qundef, t = Qundef, last = Qundef, n;
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	if (rb_num_zero_p(x))
		return BIG_ZERO;
	else if (rb_num_positive_p(x))
	{
		if (rb_num_infinite_p(x))
			return BIG_INF;
		n = rb_numdiff_make_n(prec);
		s = RTEST(rb_num_coerce_cmp(x, INT2FIX(1), '>')) ? x : BIG_ONE;
		do {
			last = s;
			t = rb_funcall1(x, '/', s);
			t = rb_funcall1(t, '+', s);
			s = rb_funcall(t, div, 2, INT2FIX(2), n);
		} while (rb_num_coerce_cmp(s, last, '<'));
		RB_GC_GUARD(s);
		RB_GC_GUARD(t);
		RB_GC_GUARD(last);
		return rb_num_round(last, prec);
	}
	else
		return BIG_NAN;
}

static VALUE
sqrt_intern(VALUE x, VALUE prec)
{
	const ID sqrt = rb_intern("sqrt");
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	if (rb_num_negative_p(x) || rb_num_notequal_p(x, x))
		return BIG_NAN;
	return rb_funcall(x, sqrt, 1, prec);
}

VALUE
rb_bigmath_sqrt(VALUE x, VALUE prec)
{
	rb_check_precise(prec);
	if (TYPE(prec) == T_FIXNUM && 
	    NUM2LONG(prec) < SWITCH_PRECISION_NUMBER)
		return sqrt_intern(x, prec);
	else
		return sqrt_newton(x, prec);
}

#undef SWITCH_PRECISION_NUMBER
