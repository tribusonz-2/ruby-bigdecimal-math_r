bool
rb_num_domain_p(VALUE range, VALUE x)
{
	const ID cover_p = rb_intern("cover?");
	VALUE ans = rb_funcall(range, cover_p, 1, x);
	return ans == Qtrue ? true : false;
}
