void
rb_check_precise(VALUE prec)
{
	const ID leq = rb_intern("<=");
	if (TYPE(prec) == T_FIXNUM || TYPE(prec) == T_BIGNUM)
	{
		if (RTEST(rb_num_coerce_cmp(prec, INT2NUM(0), leq)))
			rb_raise(rb_eRangeError, "Zero or negative precision");
	}
	else
		rb_raise(rb_eTypeError, "precision must be an Integer");
}
