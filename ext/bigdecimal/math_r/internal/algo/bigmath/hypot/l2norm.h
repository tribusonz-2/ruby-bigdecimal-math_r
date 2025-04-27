VALUE
hypot_l2norm(VALUE a, VALUE b, VALUE prec)
{
	return rb_bigmath_l2norm(rb_assoc_new(a, b), prec);
}
