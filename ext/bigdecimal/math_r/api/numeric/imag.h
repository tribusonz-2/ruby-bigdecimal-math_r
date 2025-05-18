VALUE
rb_num_imag(VALUE z)
{
	const ID imag = rb_intern("imag");
	return rb_funcall(z, imag, 0);
}
