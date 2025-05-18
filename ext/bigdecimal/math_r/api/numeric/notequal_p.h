bool
rb_num_notequal_p(VALUE lhs, VALUE rhs)
{
	const ID notequal = rb_intern("!=");
	return RTEST(rb_num_coerce_cmp(lhs, rhs, notequal));
}
