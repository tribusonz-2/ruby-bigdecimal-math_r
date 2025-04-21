VALUE
cpow_formula(VALUE z, VALUE w, VALUE prec)
{
	VALUE log = Qundef;
	rb_check_precise(prec);
	log = rb_bigmath_clog(z, prec);
	log = rb_funcall1(w, '*', log);
	return rb_bigmath_cexp(log, prec);
}
