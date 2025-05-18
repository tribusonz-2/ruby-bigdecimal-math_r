VALUE
tanh_formula(VALUE x, VALUE prec)
{
	const ID pred = rb_intern("pred");
	const ID succ = rb_intern("succ");
	const ID div = rb_intern("div");
	VALUE n = rb_numdiff_make_n(prec);
	VALUE two = rb_BigDecimal1(INT2FIX(2));
        VALUE t = rb_bigmath_exp(rb_funcall1(x, '*', two), n), y = Qundef;
	int sign;

	if (TYPE(t) == T_FIXNUM || TYPE(t) == T_BIGNUM)
	{
		y = rb_Rational(rb_funcall(t, pred, 0), rb_funcall(t, succ, 0));
	        y = rb_BigDecimal(y, prec);
	}
	else if ((sign = rb_num_infinite_p(t)) != 0)
		y = sign == 1 ? BIG_ONE : BIG_MINUS_ONE;
	else
	{
		y = rb_funcall(
			rb_funcall1(t, '-', BIG_ONE), div, 2, 
			rb_funcall1(t, '+', BIG_ONE), prec);
	}

	return y;
}
