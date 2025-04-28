VALUE
csch_exp_identity(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE n = rb_numdiff_make_n(prec);
	VALUE t = rb_bigmath_exp(x, n), y = Qundef;
	VALUE two = rb_BigDecimal1(INT2FIX(2));
	int sign;
	if (TYPE(t) == T_FIXNUM || TYPE(t) == T_BIGNUM)
	{
		y = rb_Rational(INT2FIX(1), t);
	        y = rb_funcall1(t, '-', y);
	        y = rb_funcall(two, div, 2, rb_BigDecimal(y, n), prec);
	}
	else if ((sign = rb_num_infinite_p(t)) != 0)
		y = sign == 1 ? BIG_ZERO : BIG_MINUS_ZERO;
	else
	{
		y = rb_num_canonicalize(t, prec, ARG_REAL, ARG_RECIPROCAL);
		y = rb_funcall1(t, '-', y);
		y = rb_funcall(two, div, 2, y, prec);
	}
	return y;
}
