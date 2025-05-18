VALUE
rb_bigmath_cpow(VALUE z, VALUE w, VALUE prec)
{
	return cpow_formula(z, w, prec);
}
