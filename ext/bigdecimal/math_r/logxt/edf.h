/**
 * Entity of logxt(). It is equivalent to the following Ruby code:
 * 
 * ```ruby
 *  def logxt(x, t, prec)
 *    eps = 10 ** (-prec-1)
 *    a = Rational(x); b = 1r; s = 0r;
 *    loop do
 *      a = (a * a).round(prec);  b = 0.5r * b;
 *      if a >= t
 *        s = s + b; a = a / t; 
 *      end
 *      break unless (b >= eps)
 *    end
 *    BigDecimal(s, prec)
 *  end
 *
 * ```
 */
VALUE
logxt_edf(VALUE x, VALUE t, VALUE prec)
{
	const ID mult = rb_intern("mult");
	VALUE a, b, s, one_half, n, m;
	n = rb_numdiff_make_n(prec);
	a = rb_num_canonicalize(x, n, ARG_REAL, ARG_RAWVALUE);
	b = BIG_ONE;
	s = BIG_ZERO;
	one_half = rb_BigDecimal1(rb_str_new_cstr("0.5"));
	if (rb_num_zero_p(x))
		return BIG_ZERO;
	else if (rb_num_equal_p(x, INT2FIX(1)))
		return BIG_ZERO;
	while (rb_numdiff_condition_p(s, b, n, &m))
	{
		a = rb_funcall(a, mult, 2, a, m);
		b = rb_funcall(one_half, mult, 2, b, m);
		if (RTEST(rb_num_coerce_cmp(a, t, rb_intern(">="))))
		{
			s = rb_funcall1(s, '+', b);
			a = rb_funcall1(a, '/', t);
		}
	}
	RB_GC_GUARD(b);
	RB_GC_GUARD(s);
	RB_GC_GUARD(one_half);
	return s;
}
