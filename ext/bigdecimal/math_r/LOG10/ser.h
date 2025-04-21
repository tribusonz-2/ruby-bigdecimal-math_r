VALUE
LOG10_ser(VALUE prec)
{
	VALUE x = rb_Rational(INT2FIX(-9), INT2FIX(10));
	x = log_ser_mercator(x, prec);
	return rb_num_uminus(x);
}
