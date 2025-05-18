VALUE
rb_bigmath_pow(VALUE z, VALUE w, VALUE prec)
{
	return pow_formula(z, w, prec);
}
