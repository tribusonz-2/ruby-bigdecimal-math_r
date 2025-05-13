VALUE
rb_numdiff_make_n(VALUE prec)
{
	const ID double_fig = rb_intern("double_fig");
	VALUE n;
	rb_check_precise(prec);
	n = rb_funcall(rb_funcall(rb_cBigDecimal, double_fig, 0), '+', 1, prec);
	return n;
}
