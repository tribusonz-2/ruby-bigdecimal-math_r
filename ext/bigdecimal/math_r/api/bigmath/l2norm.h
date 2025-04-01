static VALUE
bigflo_sqrt(VALUE x, VALUE prec)
{
	const ID sqrt = rb_intern("sqrt");
	const ID round = rb_intern("round");
	x = rb_funcall(x, sqrt, 1, prec);
	return rb_funcall(x, round, 1, prec);
}

static VALUE
l2norm_iter(RB_BLOCK_CALL_FUNC_ARGLIST(y, c))
{
	const ID abs2 = rb_intern("abs2");
	return rb_funcall(y, abs2, 0);
}

static VALUE
l2norm_sum(VALUE self)
{
	const ID sum = rb_intern("sum");
	return rb_block_call(self, sum, 0, NULL, l2norm_iter, Qnil);
}

static VALUE
bigmath_l2norm(VALUE vec, VALUE prec)
{
	VALUE sum;
	if (CLASS_OF(vec) != rb_cArray)
		rb_raise(rb_eTypeError, "vec must be an Array");

	sum = l2norm_sum(vec);

	switch (TYPE(sum)) {
	case T_FIXNUM:
	case T_BIGNUM:
		sum = rb_BigDecimal1(sum);
		break;
	case T_FLOAT:
		sum = rb_BigDecimal_flo(sum);
		break;
	case T_RATIONAL:
		sum = rb_BigDecimal(sum, prec);
		break;
	default:
		break;
	}
	return bigflo_sqrt(sum, prec);
}

VALUE
rb_bigmath_l2norm(VALUE vec, VALUE prec)
{
	return bigmath_l2norm(vec, prec);
}
