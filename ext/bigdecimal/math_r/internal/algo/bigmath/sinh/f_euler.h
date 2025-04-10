/**
 *  ```Ruby
 *  def sinh(x, prec)
 *    raise TypeError, "no solution for Complex" if !x.imag.zero?
 *    (Complex::I * trig_f_euler(:sin, x, prec)).real
 *  end
 *  ```
 */
VALUE
sinh_f_euler(VALUE x, VALUE prec)
{
	const ID sin = rb_intern("sin");
	VALUE y;
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	y = rb_ImaginaryZ(trig_f_euler(sin, x, prec), SIGN_PLUS);
	return rb_num_real(y);
}
