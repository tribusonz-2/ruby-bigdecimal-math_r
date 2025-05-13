bool
rb_num_nonzero_p(VALUE z)
{
	const ID nonzero_p = rb_intern("nonzero?");
	return RTEST(rb_funcall(z, nonzero_p, 0));
}
