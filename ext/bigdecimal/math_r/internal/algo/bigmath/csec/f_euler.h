/**
 *  ```Ruby
 *  def csec(z, prec)
 *    w = trig_f_euler(:cos, Complex::I * z, prec).real
 *    Complex(*w.rect.map{|x| BigDecimal(1).div(x, prec)})
 *  end
 *  ```
 */
VALUE
csec_f_euler(VALUE z, VALUE prec)
{
	const ID cos = rb_intern("cos");
	VALUE w;
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	w = trig_f_euler(cos, rb_ImaginaryZ(z, SIGN_PLUS), prec);
	return rb_num_canonicalize(w, prec, ARG_COMPLEX, ARG_RECIPROCAL);
}
