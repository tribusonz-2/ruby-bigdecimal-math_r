VALUE
atanh_logrep(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	const ID mult = rb_intern("mult");
	VALUE n, half;

	n = rb_numdiff_make_n(prec);
	half = rb_BigDecimal1(rb_str_new_cstr("0.5"));

	x = rb_funcall(
		rb_funcall1(BIG_ONE, '+', x), div, 2, 
		rb_funcall1(BIG_ONE, '-', x), n);

	return rb_funcall(half, mult, 2, rb_bigmath_log(x, n), prec);
}
