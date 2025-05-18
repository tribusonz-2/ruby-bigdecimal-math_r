VALUE
rb_num_abs(VALUE x)
{
	const ID _abs = rb_intern("abs");
	x = rb_funcall(x, _abs, 0);
	return x;
}
