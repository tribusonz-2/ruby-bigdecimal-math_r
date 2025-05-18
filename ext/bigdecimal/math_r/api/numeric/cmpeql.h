VALUE
rb_num_cmpeql(VALUE lhs, VALUE rhs)
{
	const ID cmpeql = rb_intern("<=>");
	return rb_num_coerce_cmp(lhs, rhs, cmpeql);
}
