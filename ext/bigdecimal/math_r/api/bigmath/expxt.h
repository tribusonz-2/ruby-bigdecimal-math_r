VALUE
rb_bigmath_expxt(VALUE x, VALUE t, VALUE prec)
{
	rb_check_precise(prec);
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	if (rb_num_notequal_p(x, x) ||
	    rb_num_negative_p(x) || 
	    NUM2INT(rb_num_cmpeql(x, INT2FIX(1))) == 1)
		rb_raise(rb_eRangeError, "Argument x is out of range: (0 <= x <= 1)");
	t = rb_num_canonicalize(t, prec, ARG_REAL, ARG_RAWVALUE);
	if (rb_num_notequal_p(t, t) ||
	    rb_num_negative_p(t) ||
	    NUM2INT(rb_num_cmpeql(t, INT2FIX(1))) == 1)
		rb_raise(rb_eRangeError, "Argument t is out of range: (0 <= t <= 1)");
	if (!rb_num_finite_p(x) || !rb_num_finite_p(t))
		rb_raise(rb_eFloatDomainError, "not a finite");
	return expxt_edf(x, t, prec);
}
