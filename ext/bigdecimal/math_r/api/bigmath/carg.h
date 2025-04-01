VALUE
rb_bigmath_carg(VALUE z, VALUE prec)
{
	return rb_bigmath_quadrant(
		rb_num_real(z), rb_num_imag(z), prec);
}
