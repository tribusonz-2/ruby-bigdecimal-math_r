VALUE
rb_bigmath_csqrt(VALUE z, VALUE prec)
{
	return csqrt_branch(z, prec, csqrt_formula);
}
