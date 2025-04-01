void
rb_numdiff_keep_fig(VALUE *m)
{
	const ID double_fig = rb_intern("double_fig");
	VALUE dbl_fig = rb_funcall(rb_cBigDecimal, double_fig, 0);
	if (RTEST(rb_num_coerce_cmp(*m, dbl_fig, '<')))
		*m = dbl_fig;
}
