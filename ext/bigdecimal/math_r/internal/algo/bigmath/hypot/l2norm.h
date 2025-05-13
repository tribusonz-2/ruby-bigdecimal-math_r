VALUE
hypot_l2norm(VALUE a, VALUE b, VALUE prec)
{
	VALUE w;
	
	rb_check_precise(prec);
	
	w = rb_bigmath_l2norm(rb_assoc_new(a, b), prec);
	
	return w;
}
