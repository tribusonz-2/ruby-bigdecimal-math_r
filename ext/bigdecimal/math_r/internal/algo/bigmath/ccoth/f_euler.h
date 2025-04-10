/**
 *  ```Ruby
 *  def ccoth(z, prec)
 *    w = Complex::I * trig_f_euler(:tan, z, prec)
 *    Complex(*w.rect.map{|x| BigDecimal(1).div(x, prec)})
 *  end
 *  ```
 */
VALUE
ccoth_f_euler(VALUE z, VALUE prec)
{
	const ID tan = rb_intern("tan");
	VALUE w;
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	w = rb_ImaginaryZ(trig_f_euler(tan, z, prec), SIGN_PLUS);
	return rb_num_canonicalize(w, prec, ARG_COMPLEX, ARG_RECIPROCAL);
}
