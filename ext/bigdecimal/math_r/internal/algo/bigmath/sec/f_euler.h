/**
 *  ```Ruby
 *  def sec(z, prec)
 *    w = trig_f_euler(:cos, Complex::I * z, prec).real
 *    Complex(*w.rect.map{|x| BigDecimal(1).div(x, prec)})
 *  end
 *  ```
 */
VALUE
sec_f_euler(VALUE z, VALUE prec)
{
	const ID cos = rb_intern("cos");
	VALUE w;
	z = rb_num_canonicalize(z, prec, ARG_REAL, ARG_RAWVALUE);
	w = trig_f_euler(cos, rb_ImaginaryZ(z, SIGN_PLUS), prec);
	return rb_num_canonicalize(w, prec, ARG_REAL, ARG_RECIPROCAL);
}
