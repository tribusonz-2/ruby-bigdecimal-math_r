/**
 * ```Ruby
 * def ccbrt(z, prec)
 *   log = BigMathR::LogSqrt.clog(z, prec)
 *   BigMathR::TrigExp.cexp(1/3r * log, prec)
 * end
 * ```
 */
VALUE
ccbrt_formula(VALUE z, VALUE prec)
{
	VALUE one_third = rb_Rational(INT2FIX(1), INT2FIX(3));
	return rb_bigmath_cpow(z, one_third, prec);
}
