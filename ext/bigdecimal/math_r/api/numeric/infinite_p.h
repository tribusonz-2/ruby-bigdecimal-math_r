int
rb_num_infinite_p(VALUE z)
{
	const ID infinite_p = rb_intern("infinite?");
	VALUE y = rb_funcall(z, infinite_p, 0);
	return NIL_P(y) ? 0 : NUM2INT(y);
}
