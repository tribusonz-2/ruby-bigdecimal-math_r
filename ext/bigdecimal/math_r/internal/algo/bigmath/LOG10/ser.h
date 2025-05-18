VALUE
LOG10_ser(VALUE prec)
{
#if 0
	VALUE x = rb_Rational(INT2FIX(-9), INT2FIX(10));
	x = log_ser_mercator(x, prec);
	return rb_num_uminus(x);
#else
	const ID add = rb_intern("add");
	VALUE x = rb_Rational(INT2FIX(1), INT2FIX(4)), log2;
	x = log1p_p_adic(x, prec);
	log2 = LOG2_BBP2002(prec);
	return rb_funcall(rb_funcall1(log2, '*', INT2FIX(3)), add, 2, x, prec);
#endif
}

