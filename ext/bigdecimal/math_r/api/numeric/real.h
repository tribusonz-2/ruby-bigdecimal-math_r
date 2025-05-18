VALUE
rb_num_real(VALUE z)
{
	const ID real = rb_intern("real");
	return rb_funcall(z, real, 0);
}
