/**
 *  ```Ruby
 *  def ccos(z, prec)
 *    trig_f_euler(:cos, Complex::I * z, prec)
 *  end
 *  ```
 */
VALUE
ccos_f_euler(VALUE z, VALUE prec)
{
	const ID cos = rb_intern("cos");
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return trig_f_euler(cos, rb_ImaginaryZ(z, SIGN_PLUS), prec);
}
