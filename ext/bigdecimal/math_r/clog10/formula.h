VALUE
clog10_formula(VALUE z, VALUE prec)
{
	VALUE w = clog_formula(z, prec);
	w = rb_funcall1(w, '/', rb_bigmath_const_log10(prec));
	return rb_num_round(w, prec);
}
