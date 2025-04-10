/**
 *  ```Ruby
 *  def csinh(z, prec)
 *    Complex::I * trig_f_euler(:sin, z, prec)
 *  end
 *  ```
 */
VALUE
csinh_f_euler(VALUE z, VALUE prec)
{
	const ID sin = rb_intern("sin");
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return rb_ImaginaryZ(trig_f_euler(sin, z, prec), SIGN_PLUS);
}
