/**
 *  ```Ruby
 *  def tanh(x, prec)
 *    raise TypeError, "no solution for Complex" if !x.imag.zero?
 *    (Complex::I * trig_f_euler(:tan, x, prec)).real
 *  end
 *  ```
 */
VALUE
tanh_f_euler(VALUE x, VALUE prec)
{
	const ID tan = rb_intern("tan");
	VALUE y;
	x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	y = rb_ImaginaryZ(trig_f_euler(tan, x, prec), SIGN_PLUS);
	return rb_num_real(y);
}
