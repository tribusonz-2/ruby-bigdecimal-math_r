/**
 *  ```Ruby
 *  def csin(z, prec)
 *    f_euler_sc(:sin, Complex::I * z, prec)
 *  end
 *  ```
 */
VALUE
csin_f_euler(VALUE z, VALUE prec)
{
	const ID sin = rb_intern("sin");
	z = rb_num_canonicalize(z, prec, ARG_COMPLEX, ARG_RAWVALUE);
	return trig_f_euler(sin, rb_ImaginaryZ(z, SIGN_PLUS), prec);
}
