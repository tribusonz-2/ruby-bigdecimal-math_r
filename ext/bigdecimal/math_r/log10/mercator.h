
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
log10_mercator(VALUE x, VALUE prec)
{
	const ID div = rb_intern("div");
	VALUE fra = Qundef, exp = Qundef, y = Qundef;
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	fra = rcm10_edf(x, &exp);

	y = rb_funcall1(fra, '-', INT2FIX(1));
        fra = rb_funcall(y, div, 2, fra, prec);
	fra = rb_num_uminus(fra);
	fra = log_ser_mercator(fra, prec);
	fra = rb_num_uminus(fra);
	fra = rb_funcall(fra, div, 2, rb_bigmath_const_log10(prec), prec);

	y = rb_funcall1(exp, '+', fra);
	return rb_num_round(y, prec);
}
