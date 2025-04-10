/**
 *  ```Ruby
 *  def ctan(z, prec)
 *    
 trig_f_euler(:tan, Complex::I * z, prec)
 *  end
 *  ```
 */
VALUE
ctan_f_euler(VALUE z, VALUE prec)
{
	const ID tan = rb_intern("tan");
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return trig_f_euler(tan, rb_ImaginaryZ(z, SIGN_PLUS), prec);
}
