VALUE
hypot_l2norm(VALUE a, VALUE b, VALUE prec)
{
	VALUE w, n;
	
	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	w = rb_bigmath_l2norm(rb_assoc_new(a, b), n);
	
	return rb_num_round(w, prec);
}
