#define SWITCH_PRECISION_NUMBER 2253

VALUE
rb_bigmath_sqrt(VALUE x, VALUE prec)
{
	rb_check_precise(prec);
	if (TYPE(prec) == T_FIXNUM && 
	    NUM2LONG(prec) < SWITCH_PRECISION_NUMBER)
		return sqrt_builtin(x, prec);
	else
		return sqrt_newton(x, prec);
}

#undef SWITCH_PRECISION_NUMBER
