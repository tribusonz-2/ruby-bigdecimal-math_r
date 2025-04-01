bool
rb_num_negative_p(VALUE z)
{
	const ID negative_p = rb_intern("negative?");
	return RTEST(rb_funcall(z, negative_p, 0));
}
