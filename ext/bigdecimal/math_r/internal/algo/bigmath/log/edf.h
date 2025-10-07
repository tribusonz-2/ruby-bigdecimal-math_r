VALUE
log_edf(VALUE x, VALUE prec)
{
	VALUE y = Qundef, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	y = logxt_edf(x, INT2FIX(2), n);
	y = rb_funcall1(y, '*', rb_bigmath_const_log2(n));

	return rb_num_round(y, prec);
}
