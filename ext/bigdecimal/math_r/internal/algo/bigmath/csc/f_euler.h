/**
 *  ```Ruby
 *  def csc(z, prec)
 *    w = trig_f_euler(:sin, Complex::I * z, prec)
 *    Complex(*w.rect.map{|x| BigDecimal(1).div(x, prec)})
 *  end
 *  ```
 */
VALUE
csc_f_euler(VALUE z, VALUE prec)
{
	const ID sin = rb_intern("sin");
	VALUE w;
	z = rb_num_canonicalize(z, prec, ARG_REAL, ARG_RAWVALUE);
	w = trig_f_euler(sin, rb_ImaginaryZ(z, SIGN_PLUS), prec);
	return rb_num_canonicalize(w, prec, ARG_REAL, ARG_RECIPROCAL);
}
