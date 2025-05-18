VALUE
rb_BigDecimal_sign(VALUE d)
{
        const ID sign = rb_intern("sign");
	if (TYPE(d) == T_FIXNUM || TYPE(d) == T_BIGNUM)
		d = rb_BigDecimal1(d);
	else if (CLASS_OF(d) != rb_cBigDecimal)
		rb_raise(rb_eTypeError, "not a BigDecimal: rb_BigDecimal_sign()");
        return rb_funcall(d, sign, 0);
}
