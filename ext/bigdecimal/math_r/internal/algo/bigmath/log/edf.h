VALUE
log_edf(VALUE x, VALUE prec)
{
	VALUE fra = Qundef, exp = Qundef, y = Qundef;
	fra = rcm2_edf(x, &exp);
	fra = logxt_edf(fra, INT2FIX(2), prec);
	exp = rb_funcall1(exp, '+', fra);
	y = rb_funcall1(exp, '*', rb_bigmath_const_log2(prec));
	return rb_num_round(y, prec);
}
