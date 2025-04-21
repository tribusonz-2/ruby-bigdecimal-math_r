VALUE
log2_edf(VALUE x, VALUE prec)
{
	VALUE fra = Qundef, exp = Qundef, y = Qundef;
	fra = rcm2_edf(x, &exp);
	fra = logxt_edf(fra, INT2FIX(2), prec);
	y = rb_funcall1(exp, '+', fra);
	return rb_num_round(y, prec);
}
