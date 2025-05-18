VALUE
asech_edom(VALUE x, VALUE prec)
{
	VALUE absx, recip_x, sqr, w, y;

	absx = rb_num_abs(x);
	recip_x = rb_num_canonicalize(absx, prec, ARG_REAL, ARG_RECIPROCAL);
	sqr = rb_funcall1(
		rb_funcall1(BIG_ONE, '-', absx), '/', 
		rb_funcall1(absx, '+', BIG_ONE));
	w = rb_Complex(BIG_ZERO, rb_bigmath_sqrt(sqr, prec));
	w = rb_funcall1(w, '*', rb_funcall1(recip_x, '+', BIG_ONE));
	w = rb_funcall1(w, '+', recip_x);
	y = rb_bigmath_carg(w, prec);
	if (rb_num_negative_p(x))
		y =rb_funcall1(rb_bigmath_const_pi(prec), '-', y);

	return rb_Complex(BIG_ZERO, y);
}
