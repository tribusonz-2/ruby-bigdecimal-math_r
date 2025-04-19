VALUE
clog2_formula(VALUE z, VALUE prec)
{
	VALUE w = clog_formula(z, prec);
	w = rb_funcall1(w, '/', rb_bigmath_const_log2(prec));
	return rb_num_round(w, prec);
}
