/**
 *  ```Ruby
 *  def ccsch(z, prec)
 *    w = Complex::I * trig_f_euler(:sin, z, prec)
 *    Complex(*w.rect.map{|x| BigDecimal(1).div(x, prec)})
 *  end
 *  ```
 */
VALUE
ccsch_f_euler(VALUE z, VALUE prec)
{
	const ID sin = rb_intern("sin");
	VALUE w;
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	w = rb_ImaginaryZ(trig_f_euler(sin, z, prec), SIGN_PLUS);
	return rb_num_canonicalize(w, prec, ARG_COMPLEX, ARG_RECIPROCAL);
}
