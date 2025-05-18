
#if 0
static VALUE
log_ser_mercator_x(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE y;
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	y = rb_funcall1(x, '-', INT2FIX(1));
	y = rb_funcall(y, div, 2, x, prec);
	y = rb_num_uminus(y);
	return y;
}
#endif

VALUE
log_mercator(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE fra = Qundef, exp = Qundef, y = Qundef;
	fra = rcm2_edf(x, &exp);

	rb_check_precise(prec);

	y = rb_funcall1(fra, '-', INT2FIX(1));
        fra = rb_funcall(y, div, 2, fra, prec);
	fra = rb_num_uminus(fra);
	fra = log1p_ser_mercator(fra, prec);
	fra = rb_num_uminus(fra);

	exp = rb_funcall1(exp, '*', rb_bigmath_const_log2(prec));
	y = rb_funcall1(exp, '+', fra);
	return rb_num_round(y, prec);
}
