VALUE
rb_bigmath_sqrt(VALUE x, VALUE prec)
{
	return sqrt_branch(x, prec, sqrt_newton);
}
