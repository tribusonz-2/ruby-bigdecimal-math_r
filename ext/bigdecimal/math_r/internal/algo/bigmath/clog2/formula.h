VALUE
clog2_formula(VALUE z, VALUE prec)
{
	VALUE w, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	w = rb_bigmath_clog(z, n);
	w = rb_funcall1(w, '/', rb_bigmath_const_log2(n));

	return rb_num_round(w, prec);
}
