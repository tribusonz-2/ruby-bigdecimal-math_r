VALUE
cexp2_eulerf(VALUE z, VALUE prec)
{
	VALUE log2 = rb_bigmath_const_log2(prec);

	rb_check_precise(prec);

	z = rb_funcall1(z, '*', log2);
	z = cexp_eulerf(z, prec);

	return z;
}
