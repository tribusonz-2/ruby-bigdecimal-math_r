/**
 *  ```Ruby
 *  def sech(x, prec)
 *    raise TypeError, "no solution for Complex" if !x.imag.zero?
 *    y = trig_f_euler(:cos, x, prec).real
 *    (BigDecimal(1).div(y, prec)).real
 *  end
 *  ```
 */
VALUE
sech_f_euler(VALUE x, VALUE prec)
{
	const ID cos = rb_intern("cos");
	VALUE y;
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	y = trig_f_euler(cos, x, prec);
	return rb_num_canonicalize(y, prec, ARG_REAL, ARG_RECIPROCAL);
}
