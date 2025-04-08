VALUE
log10_edf(VALUE x, VALUE prec)
{
	VALUE fra = Qundef, exp = Qundef, y = Qundef;
	fra = rcm10_edf(x, &exp);
	fra = logxt_edf(fra, INT2FIX(10), prec);
	y = rb_funcall1(exp, '+', fra);
	return rb_num_round(y, prec);
}
