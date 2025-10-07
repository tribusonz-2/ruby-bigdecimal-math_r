VALUE
cexpm1_identity(VALUE x, VALUE prec)
{
	VALUE y = Qundef;
	VALUE two = rb_BigDecimal1(INT2FIX(2));
	VALUE n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	x = rb_funcall1(x, '/', two);

	y = rb_funcall1(rb_bigmath_cexp(x, n), '*', csinh_branch(x, n, csinh_eulerf));
	y = rb_funcall1(two, '*', y);

	return rb_num_round(y, prec);
}
