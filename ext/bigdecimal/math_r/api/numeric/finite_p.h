bool
rb_num_finite_p(VALUE z)
{
	const ID finite_p = rb_intern("finite?");
	return RTEST(rb_funcall(z, finite_p, 0));
}
