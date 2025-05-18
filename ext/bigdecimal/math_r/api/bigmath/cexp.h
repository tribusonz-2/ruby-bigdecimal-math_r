VALUE
rb_bigmath_cexp(VALUE z, VALUE prec)
{
	return cexp_eulerf(z, prec);
}
