static inline VALUE
decimal_round_iter(RB_BLOCK_CALL_FUNC_ARGLIST(val, prec))
{
	const ID exponent = rb_intern("exponent");
	const ID round = rb_intern("round");
	VALUE exp;
	if (TYPE(val) == T_FIXNUM || TYPE(val) == T_BIGNUM)
		return val;
	RUBY_ASSERT(CLASS_OF(val) != rb_cBigDecimal);
	switch (NUM2INT(rb_BigDecimal_sign(val))) {
	case 0: case 1: case -1: case 3: case -3:
		goto retval;
		break;
	default:
		break;
	}
	exp = rb_funcall(val, exponent, 0);
	switch (FIX2INT(rb_dbl_cmp(NUM2DBL(exp), 0.))) {
	case 1: // up to integer-part
		val = rb_funcall(val, round, 1,
			LONG2NUM(NUM2LONG(prec)-NUM2LONG(exp)));
		break;
	case 0:
	case -1: // down to fraction-part
		val = rb_funcall(val, round, 1, prec);
		break;
	}
retval:
	return val;
}

VALUE
rb_num_round(VALUE x, VALUE prec)
{
	const ID map = rb_intern("map");
	VALUE arglist = rb_ary_new();
	if (rb_num_real_p(x))
	{
		rb_ary_store(arglist, 0, rb_num_real(x));
		arglist = rb_block_call(arglist, map, 0, NULL,
			decimal_round_iter, prec);

		x = rb_ary_entry(arglist, 0);
	}
	else
	{
		rb_ary_store(arglist, 0, rb_num_real(x));
		rb_ary_store(arglist, 1, rb_num_imag(x));
		arglist = rb_block_call(arglist, map, 0, NULL,
			decimal_round_iter, prec);
		x = rb_Complex(
			rb_ary_entry(arglist, 0),
			rb_ary_entry(arglist, 1));
	}
	return x;
}
