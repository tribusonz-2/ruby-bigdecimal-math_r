static inline void
rb_numdiff_keep_fig(VALUE *m)
{
	const ID double_fig = rb_intern("double_fig");
	VALUE dbl_fig = rb_funcall(rb_cBigDecimal, double_fig, 0);
	if (RTEST(rb_num_coerce_cmp(*m, dbl_fig, '<')))
		*m = dbl_fig;
}

bool
rb_numdiff_condition_p(VALUE y, VALUE d, VALUE n, VALUE *m)
{
	const ID exponent = rb_intern("exponent");
	const ID abs = rb_intern("abs");
	*m = rb_funcall(n, '-', 1, 
	       rb_funcall(
	         rb_funcall(
	           rb_funcall(y, exponent, 0), '-', 1, 
	           rb_funcall(d, exponent, 0)
	         ), abs, 0
	       )
	     );
	if (rb_num_positive_p(*m))
		rb_numdiff_keep_fig(m);
	return rb_num_nonzero_p(d) && rb_num_positive_p(*m);
}
