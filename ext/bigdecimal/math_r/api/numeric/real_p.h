bool
rb_num_real_p(VALUE z)
{
	const ID real_p = rb_intern("real?");
	return RTEST(rb_funcall(z, real_p, 0));
}
