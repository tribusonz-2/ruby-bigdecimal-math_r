VALUE
cexp2_f_euler(VALUE z, VALUE prec)
{
	VALUE log2 = rb_bigmath_const_log2(prec);
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	z = rb_funcall1(z, '*', log2);
	return cexp_f_euler(z, prec);
}
