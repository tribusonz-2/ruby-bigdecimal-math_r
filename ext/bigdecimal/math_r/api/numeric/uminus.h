VALUE
rb_num_uminus(VALUE x)
{
	const ID uminus = rb_intern("-@");
	return rb_funcall(x, uminus, 0);
}
