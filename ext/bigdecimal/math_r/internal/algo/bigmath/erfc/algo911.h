VALUE
erfc_algo911(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	const ID leq = rb_intern("<=");
	const ID pow = rb_intern("**");
	VALUE bc, n, log10, y = Qundef;
	VALUE zero_seven = rb_BigDecimal1(rb_str_new_cstr("0.7"));
	VALUE nine = rb_BigDecimal1(INT2FIX(9));

	n = rb_numdiff_make_n(prec);

	log10 = rb_bigmath_const_log10(n);

	bc = rb_funcall1(prec, '+', INT2FIX(6));
	bc = rb_funcall1(bc, '*', log10);
	bc = rb_funcall1(bc, pow, zero_seven);
	bc = rb_funcall(bc, div, 2, nine, n);
	if (rb_num_coerce_cmp(x, bc, leq))
	{
		y = erf_algo911(x, prec);
		y = rb_funcall1(BIG_ONE, '-', y);
	}
	else
	{
		y = erfc_cf(x, prec);
	}
	return y;
}
