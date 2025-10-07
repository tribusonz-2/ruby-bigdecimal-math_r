VALUE
SQRT2_builtin(VALUE prec)
{
	rb_check_precise(prec);
	VALUE n = rb_numdiff_make_n(prec);
	VALUE x = rb_bigmath_sqrt(INT2FIX(2), n);
	return rb_num_round(x, prec);
}
