VALUE
cexp2_eulerf(VALUE z, VALUE prec)
{
	VALUE log2, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	log2 = rb_bigmath_const_log2(n);
	z = rb_funcall1(z, '*', log2);
	z = cexp_eulerf(z, n);

	return rb_num_round(z, prec);
}
