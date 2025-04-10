/**
 *  ```Ruby
 *  def csch(x, prec)
 *    raise TypeError, "no solution for Complex" if !x.imag.zero?
 *    y = Complex::I * trig_f_euler(:sin, x, prec).real
 *    (BigDecimal(1).div(y, prec)).real
 *  end
 *  ```
 */
VALUE
csch_f_euler(VALUE x, VALUE prec)
{
	const ID sin = rb_intern("sin");
	VALUE y;
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	y = rb_ImaginaryZ(trig_f_euler(sin, x, prec), SIGN_PLUS);
	return rb_num_canonicalize(y, prec, ARG_REAL, ARG_RECIPROCAL);
}
