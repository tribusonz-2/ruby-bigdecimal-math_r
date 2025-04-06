VALUE
rb_bigmath_ipow(VALUE x, VALUE n, VALUE exp)
{
	VALUE y;
	
	rb_check_precise(exp);
	x = rb_num_canonicalize(x, exp, ARG_REAL, ARG_RAWVALUE);
	if (!(TYPE(n) == T_FIXNUM || TYPE(n) == T_BIGNUM))
		rb_raise(rb_eTypeError, "right-hand side must be an Integer");
	
	y = ipow_edf(x, n, exp);
	
	return y;
}
