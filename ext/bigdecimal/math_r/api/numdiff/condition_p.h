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
	return rb_num_nonzero_p(d) && RTEST(rb_num_coerce_cmp(*m, INT2FIX(0), '>'));
}
