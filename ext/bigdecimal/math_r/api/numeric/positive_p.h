bool
rb_num_positive_p(VALUE z)
{
	const ID positive_p = rb_intern("positive?");
	return RTEST(rb_funcall(z, positive_p, 0));
}
