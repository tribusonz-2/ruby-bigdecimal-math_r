/**
 * 
 *  Implementation is equivalent as follow:
 *  ```Ruby
 *  def intpower(x, n, exp)
 *    eps = 10 ** exp
 *    if !n.finite?
 *      case n.infinite?
 *      when 1
 *        return BigDecimal::INFINITY
 *      when -1
 *        return Rational(0)
 *      when nil
 *        return BigDecimal::NAN
 *      end
 *    end
 *    x = Rational(x)
 *    abs_n = n.abs;  r = 1;
 *    while (abs_n != 0)
 *      if (abs_n & 1 == 1)
 *        r *= x
 *        if r > eps
 *          r = BigDecimal::INFINITY
 *        end
 *      end
 *      break if r.infinite?
 *      x *= x;  abs_n >>= 1;
 *    end
 *    (n >= 0) ? r : 1 / r
 *  end
 *  ```
 * 
 */
VALUE
ipow_edf(VALUE x, VALUE n, VALUE exp)
{
	const ID mult = rb_intern("mult");
	const ID exponent = rb_intern("exponent");
	const ID r_shift = rb_intern(">>");
	const ID geq = rb_intern(">=");
	VALUE abs_n = Qundef, r = Qundef;
	if (!rb_num_finite_p(x))
		return BIG_NAN;
	x = rb_num_canonicalize(x, exp, ARG_REAL, ARG_RAWVALUE);
	abs_n = n;
	if (rb_num_negative_p(n))  abs_n = rb_num_uminus(abs_n); // abs()
	r = BIG_ONE;
	while (rb_num_nonzero_p(abs_n))
	{
		if (RTEST(NUM2INT(rb_num_coerce_bit(abs_n, INT2FIX(1), '&'))))
		{
			r = rb_funcall(r, mult, 2, x, exp);
			if (RTEST(rb_num_coerce_cmp(rb_funcall(
			r, exponent, 0), exp, '>')))
				r = BIG_INF;
		}
		if (rb_num_infinite_p(r))
			break;
		x = rb_funcall(x, mult, 2, x, exp);
		abs_n = rb_num_coerce_bit(abs_n, INT2FIX(1), r_shift);
	}
	return RTEST(rb_num_coerce_cmp(n, INT2FIX(0), geq)) ?
		r : rb_funcall1(INT2FIX(1), '/', r);
}
