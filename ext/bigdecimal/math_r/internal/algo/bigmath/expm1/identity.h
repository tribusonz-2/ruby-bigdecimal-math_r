VALUE
expm1_identity(VALUE x, VALUE prec)
{
	const ID mult = rb_intern("mult");
	VALUE y = Qundef;
	VALUE two = rb_BigDecimal1(INT2FIX(2));
	VALUE n;

	n = rb_numdiff_make_n(prec);

	x = rb_funcall1(x, '/', two);

	y = rb_funcall1(rb_bigmath_exp(x, n), '*', sinh_branch(x, n, sinh_formula));
	y = rb_funcall(two, mult, 2, y, prec);

	return y;
}
