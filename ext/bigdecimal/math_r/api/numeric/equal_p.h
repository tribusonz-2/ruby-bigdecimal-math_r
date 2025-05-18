bool
rb_num_equal_p(VALUE lhs, VALUE rhs)
{
	const ID equal = rb_intern("==");
	return RTEST(rb_num_coerce_cmp(lhs, rhs, equal));
}
