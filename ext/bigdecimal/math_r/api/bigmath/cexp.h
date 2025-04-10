/**
 *  ```Ruby
 *  def cexp(z, prec)
 *    cexp_f_euler(z, prec)
 *  end
 *  ```
 */
VALUE
rb_bigmath_cexp(VALUE z, VALUE prec)
{
	return cexp_f_euler(z, prec);
}
