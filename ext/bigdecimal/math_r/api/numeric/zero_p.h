bool
rb_num_zero_p(VALUE z)
{
	const ID zero_p = rb_intern("zero?");
	return RTEST(rb_funcall(z, zero_p, 0));
}
