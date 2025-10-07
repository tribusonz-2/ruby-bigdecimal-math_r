
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
	VALUE temp = Qundef, y = Qundef, n;

	rb_check_precise(prec);
	n = rb_numdiff_make_n(prec);

	y = rb_funcall1(temp, '-', INT2FIX(1));
        temp = rb_funcall(y, div, 2, temp, n);
	temp = rb_num_uminus(temp);
	temp = log1p_ser_mercator(temp, n);
	y = rb_num_uminus(temp);

	return rb_num_round(y, prec);
}
