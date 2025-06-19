VALUE
clog2_formula(VALUE z, VALUE prec)
{
	VALUE w;

	rb_check_precise(prec);

	w = rb_bigmath_clog(z, prec);
	w = rb_funcall1(w, '/', rb_bigmath_const_log2(prec));

	return rb_num_round(w, prec);
}
