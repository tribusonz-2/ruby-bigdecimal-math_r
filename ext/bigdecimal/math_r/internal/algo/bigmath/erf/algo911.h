VALUE
erf_algo911(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	const ID leq = rb_intern("<=");
	const ID pow = rb_intern("**");
	VALUE absx, bc, log10, n, y = Qundef;
	VALUE zero_six = rb_BigDecimal1(rb_str_new_cstr("0.6"));
	VALUE four_one = rb_BigDecimal1(rb_str_new_cstr("4.1"));

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	absx = rb_num_abs(x);
	log10 = rb_bigmath_const_log10(n);

	bc = rb_BigDecimal1(rb_funcall1(n, '+', INT2FIX(21)));
	bc = rb_funcall1(bc, '*', log10);
	bc = rb_bigmath_sqrt(bc, n);
	bc = rb_funcall(bc, div, 2, INT2FIX(5), n);
	if (rb_num_coerce_cmp(absx, bc, leq))
	{
		y = erf_ser_zero(absx, prec);
		goto retval;
	}
	bc = rb_funcall1(prec, '+', INT2FIX(6));
	bc = rb_funcall1(bc, '*', log10);
	bc = rb_funcall1(bc, pow, zero_six);
	bc = rb_funcall(bc, div, 2, four_one, n);
       if (rb_num_coerce_cmp(absx, bc, leq))
        {
                y = erf_ser_inf(absx, prec);
		goto retval;
        }
	else
	{
		y = erf_cf(absx, prec);
		goto retval;
	}
retval:
	if (rb_num_negative_p(x))
		y = rb_num_uminus(y);
	return y;
}
