/**
 *  ```Ruby
 *  def ctanh(z, prec)
 *    Complex::I * trig_f_euler(:tan, z, prec)
 *  end
 *  ```
 */
VALUE
ctanh_f_euler(VALUE z, VALUE prec)
{
	const ID tan = rb_intern("tan");
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_ImaginaryZ(trig_f_euler(tan, z, prec), SIGN_PLUS);
}
