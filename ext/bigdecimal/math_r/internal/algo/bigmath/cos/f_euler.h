/**
 *  ```Ruby
 *  def cos(z, prec)
 *    trig_f_euler(:cos, Complex::I * z, prec)
 *  end
 *  ```
 */
VALUE
cos_f_euler(VALUE z, VALUE prec)
{
	const ID cos = rb_intern("cos");
	z = rb_num_canonicalize(z, prec, ARG_REAL, ARG_RAWVALUE);
	z = trig_f_euler(cos, rb_ImaginaryZ(z, SIGN_PLUS), prec);
	return rb_num_real(z);
}
