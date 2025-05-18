VALUE
atanh_edom(VALUE x, VALUE prec)
{
	VALUE t, pi;

	t = rb_funcall1(
		rb_funcall1(BIG_ONE, '+', x), '/', 
		rb_funcall1(BIG_ONE, '-', x));
	pi = rb_bigmath_const_pi(prec);
	t = rb_Complex(
		rb_bigmath_log(rb_num_abs(t), prec), 
		rb_num_negative_p(x) ? pi : rb_num_uminus(pi));
	t = rb_funcall1(rb_Rational(INT2FIX(1), INT2FIX(2)), '*', t);

	return rb_num_round(t, prec);
}
