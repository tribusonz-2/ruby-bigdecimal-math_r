/**
 * It is equivalent to the following Ruby code:
 *  ```Ruby
 *  def sincos_to_radian(x, prec)
 *    twopi = BigMath.PI(prec) * BigDecimal(2)
 *    if x < -twopi or twopi < x
 *      x = -x if neg = x < 0
 *      if x > 30
 *        x %= twopi
 *      else
 *        x -= twopi while x > twopi
 *      end
 *      x = -x if neg
 *    else
 *      x = case x
 *      when Integer
 *        BigDecimal(x)
 *      when Float
 *        BigDecimal(x, Float::DIG)
 *      when Rational
 *        BigDecimal(x, prec)
 *      when Complex
 *        raise TypeError, "no solution for Complex"
 *      else
 *        x
 *      end
 *    end
 *    if x < (-twopi/2)
 *      x + twopi
 *    elsif (twopi/2) < x
 *      x - twopi
 *    else
 *      x
 *    end
 *  end
 *  ```
 */
static VALUE
sincos_to_radian(VALUE x, VALUE prec, VALUE pi, VALUE *t)
{
	const ID mult = rb_intern("mult");
	VALUE twopi = rb_funcall1(pi, '*', INT2FIX(2));
	bool neg = false;
	if (NUM2INT(rb_num_cmpeql(x, rb_num_uminus(twopi))) == -1 ||
	    NUM2INT(rb_num_cmpeql(twopi, x)) == -1)
	{
		neg = rb_num_negative_p(x);
		if (neg)
			x = rb_num_uminus(x);
		if (rb_num_cmpeql(x, INT2FIX(30)) == 1)
			x = rb_funcall1(x, '%', twopi);
		else
			do x = rb_funcall1(x, '-', twopi);
				while (INT2FIX(rb_num_cmpeql(x, twopi)) == 1);
		if (neg)
			x = rb_num_uminus(x);
	}
	else
	{
		x = rb_num_canonicalize(x, prec, ARG_REAL, ARG_RAWVALUE);
	}
	if (t != NULL)
	{
		*t = rb_num_round(
			rb_funcall1(x, '/', twopi), prec);
		if (rb_num_negative_p(*t))
			rb_funcall1(x, '+', INT2FIX(1));
		*t = rb_funcall(*t, mult, 2, INT2FIX(360), prec);
	}
	if (NUM2INT(rb_num_cmpeql(x, rb_num_uminus(pi))) == -1)
		x = rb_funcall1(x, '+', twopi);
	else if   (NUM2INT(rb_num_cmpeql(pi, x)) == -1)
		x = rb_funcall1(x, '-', twopi);
	return x;
}


/**
 *  Degree  | Rational | $P(x, y) = (\cos\theta, \sin\theta)$
 *  360-deg |      0/1 | $(1, 0)$
 *   30-deg |      1/6 | $(\frac{\sqrt{3}}{2}, \frac{1}{2})$
 *   45-deg |      1/4 | $(\frac{\sqrt{2}}{2}, \frac{\sqrt{2}}{2})$
 *   60-deg |      1/3 | $(\frac{1}{2}, \frac{\sqrt{3}}{2})$
 *   90-deg |      1/2 | $(0, 1)$
 *  120-deg |      2/3 | $(-\frac{1}{2}, \frac{\sqrt{3}}{2})$
 *  135-deg |      3/4 | $(-\frac{\sqrt{2}}{2}, \frac{\sqrt{2}}{2})$
 *  150-deg |      5/6 | $(-\frac{\sqrt{3}}{2}, \frac{1}{2})$
 *  180-deg |      1/1 | $(-1, 0)$
 *  210-deg |      7/6 | $(-\frac{\sqrt{3}}{2}, -\frac{1}{2})$
 *  225-deg |      5/4 | $(-\frac{\sqrt{2}}{2}, -\frac{\sqrt{2}}{2})$
 *  240-deg |      4/3 | $(-\frac{1}{2}, -\frac{\sqrt{3}}{2})$
 *  270-deg |      3/2 | $(0, -1)$
 *  300-deg |      5/3 | $(\frac{1}{2}, -\frac{\sqrt{3}}{2})$
 *  315-deg |      7/4 | $(\frac{\sqrt{2}}{2}, -\frac{\sqrt{2}}{2})$
 *  330-deg |     11/6 | $(\frac{\sqrt{3}}{2}, -\frac{1}{2})$
 *
 *  ```Ruby
 *  def sparg_list(prec)
 *    funcs = [:sin, :cos, :tan, :csc, :sec, :cot]
 *    degrees = [
 *      0/1r, 1/6r, 1/4r, 1/3r, 1/2r, 2/3r, 3/4r, 5/6r,
 *        1r, 7/6r, 5/4r, 4/3r, 3/2r, 5/3r, 7/4r, 11/6r
 *    ]
 *    degree_num = [
 *      360,  30,  45,  60,  90, 120, 135, 150,
 *      180, 210, 225, 240, 270, 300, 315, 330
 *    ]
 *    pi = BigMath.PI(prec)
 *  
 *    puts (["Degree"] + funcs).map{|func| (" " + func.to_s).ljust(prec+5, " ")}.join("  ")
 *  
 *    degree_num.zip(degrees).each do |deg, rat|
 *      list = [deg]
 *      funcs.each do |func|
 *        meth = BigMathR::Trigonometric.method(func)
 *        y = meth.call(rat * pi, prec)
 *        list << y
 *      end
 *      puts list.map{|x| ((x = x.to_s)[0] == '-' ? x : " " + x.to_s).ljust(prec+5, " ")}.join("  ")
 *    end
 *  end
 *  ```
 *  
 *  ```
 *  $ sparg_list(8)
 *   Degree         sin            cos            tan            csc            sec            cot         
 *   360            0.0            0.1e1          0.0            Infinity       0.1e1          Infinity    
 *   30             0.5e0          0.8660254e0    0.57735027e0   0.2e1          0.11547005e1   0.17320508e1
 *   45             0.70710678e0   0.70710678e0   0.1e1          0.14142136e1   0.14142136e1   0.1e1       
 *   60             0.8660254e0    0.5e0          0.17320508e1   0.11547005e1   0.2e1          0.57735027e0
 *   90             0.1e1          0.0            Infinity       0.1e1          Infinity       0.0         
 *   120            0.8660254e0   -0.5e0         -0.17320508e1   0.11547005e1  -0.2e1         -0.57735027e0
 *   135            0.70710678e0  -0.70710678e0  -0.1e1          0.14142136e1  -0.14142136e1  -0.1e1       
 *   150            0.5e0         -0.8660254e0   -0.57735027e0   0.2e1         -0.11547005e1  -0.17320508e1
 *   180            0.0           -0.1e1         -0.0            Infinity      -0.1e1         -Infinity    
 *   210           -0.5e0         -0.8660254e0    0.57735027e0  -0.2e1         -0.11547005e1   0.17320508e1
 *   225           -0.70710678e0  -0.70710678e0   0.1e1         -0.14142136e1  -0.14142136e1   0.1e1       
 *   240           -0.8660254e0   -0.5e0          0.17320508e1  -0.11547005e1  -0.2e1          0.57735027e0
 *   270           -0.1e1          0.0           -Infinity      -0.1e1          Infinity      -0.0         
 *   300           -0.8660254e0    0.5e0         -0.17320508e1  -0.11547005e1   0.2e1         -0.57735027e0
 *   315           -0.70710678e0   0.70710678e0  -0.1e1         -0.14142136e1   0.14142136e1  -0.1e1       
 *   330           -0.5e0          0.8660254e0   -0.57735027e0  -0.2e1          0.11547005e1  -0.17320508e1
 *  ```
 * --------------------------------- SYNOPSIS ---------------------------------
 */

static int
degree_sparg(VALUE t, VALUE prec, VALUE *sin, VALUE *cos)
{
	const ID div = rb_intern("div");
#define angle_equal_p(d) \
	rb_num_equal_p(t, INT2FIX(d))
#define HALF \
	rb_funcall(BIG_ONE, div, 2, INT2FIX(2), prec)
#define HALF_M \
	rb_funcall(BIG_ONE, div, 2, INT2FIX(-2), prec)
#define SQRT2_2 \
	rb_funcall(rb_bigmath_const_sqrt2(prec), div, 2, INT2FIX(2), prec)
#define SQRT2_2_M \
	rb_funcall(rb_bigmath_const_sqrt2(prec), div, 2, INT2FIX(-2), prec)
#define SQRT3_2 \
	rb_funcall(rb_bigmath_const_sqrt3(prec), div, 2, INT2FIX(2), prec)
#define SQRT3_2_M \
	rb_funcall(rb_bigmath_const_sqrt3(prec), div, 2, INT2FIX(-2), prec)

	if (angle_equal_p(0))
	{
		if (cos != NULL)  *cos = BIG_ONE;
		if (sin != NULL)  *sin = BIG_ZERO;
		return 1;
	}
	else if (angle_equal_p(30))
	{
		if (cos != NULL)  *cos = SQRT3_2;
		if (sin != NULL)  *sin = HALF;
		return 1;
	}
	else if (angle_equal_p(45))
	{
		if (cos != NULL)  *cos = SQRT2_2;
		if (sin != NULL)  *sin = SQRT2_2;
		return 1;
	}
	else if (angle_equal_p(60))
	{
		if (cos != NULL)  *cos = HALF;
		if (sin != NULL)  *sin = SQRT3_2;

		return 1;
	}
	else if (angle_equal_p(90))
	{
		if (cos != NULL)  *cos = BIG_ZERO;
		if (sin != NULL)  *sin = BIG_ONE;
		return 1;
	}
	else if (angle_equal_p(120))
	{
		if (cos != NULL)  *cos = HALF_M;
		if (sin != NULL)  *sin = SQRT3_2;
		return 1;
	}
	else if (angle_equal_p(135))
	{
		if (cos != NULL)  *cos = SQRT2_2_M;
		if (sin != NULL)  *sin = SQRT2_2; 
		return 1;
	}
	else if (angle_equal_p(150))
	{
		if (cos != NULL)  *cos = SQRT3_2_M;
		if (sin != NULL)  *sin = HALF;
		return 1;
	}
	else if (angle_equal_p(180))
	{
		if (cos != NULL)  *cos = BIG_MINUS_ONE;
		if (sin != NULL)  *sin = BIG_ZERO;
		return 1;
	}
	else if (angle_equal_p(210))
	{
		if (cos != NULL)  *cos = SQRT3_2_M;
		if (sin != NULL)  *sin = HALF_M;
		return 1;
	}
	else if (angle_equal_p(225))
	{
		if (cos != NULL)  *cos = SQRT2_2_M;
		if (sin != NULL)  *sin = SQRT2_2_M;
		return 1;
	}
	else if (angle_equal_p(240))
	{
		if (cos != NULL)  *cos = HALF_M;
		if (sin != NULL)  *sin = SQRT3_2_M;
		return 1;
	}
	else if (angle_equal_p(270))
	{
		if (cos != NULL)  *cos = BIG_ZERO;
		if (sin != NULL)  *sin = BIG_MINUS_ONE;
		return 1;
	}
	else if (angle_equal_p(300))
	{
		if (cos != NULL)  *cos = HALF;
		if (sin != NULL)  *sin = SQRT3_2_M;
		return 1;
	}
	else if (angle_equal_p(315))
	{
		if (cos != NULL)  *cos = SQRT2_2;
		if (sin != NULL)  *sin = SQRT2_2_M;
		return 1;
	}
	else if (angle_equal_p(330))
	{
		if (cos != NULL)  *cos = SQRT3_2;
		if (sin != NULL)  *sin = HALF_M;
		return 1;
	}
#undef angle_equal_p
#undef HALF
#undef HALF_M
#undef SQRT2_2
#undef SQRT2_2_M
#undef SQRT3_2
#undef SQRT3_2_M
	else
	{
		return -1;
	}
}

/**
 *  It is equivalent to the following Ruby code:
 *  ```Ruby
 *  def sincos(func, x, prec)
 *    raise TypeError, "precision must be an Integer" unless prec.class == Integer
 *    raise RangeError, "zero or negative precision" if prec <= 0
 *    calc_sin = false; calc_cos = false
 *    case func
 *    when :sin, :csc
 *      calc_sin = true
 *    when :cos, :sec
 *      calc_cos = true
 *    when :sincos, :tan, :cot
 *      calc_sin = true; calc_cos = true
 *    else
 *      raise ArgumentError, "unrecognized function name: #{func}"
 *    end
 *  
 *    return BigDecimal::NAN if x.infinite? or x != x
 *    n = prec + BigDecimal.double_fig
 *    x = sincos_to_radian(x, prec)
 *    i = 0
 *    f = BigDecimal(1)
 *    w = BigDecimal(1)
 *    a = BigDecimal(1)
 *    sin = BigDecimal(0)
 *    cos = BigDecimal(0)
 *    while a.nonzero? && (m = (n - f.exponent).abs) > 0
 *      m = BigDecimal.double_fig if m < BigDecimal.double_fig
 *      a = w.div(f, m)
 *      case i % 4
 *      when 0
 *        cos += a if calc_cos
 *      when 1
 *        sin += a if calc_sin
 *      when 2
 *        cos -= a if calc_cos
 *      when 3
 *        sin -= a if calc_sin
 *      end
 *      w = w.mult(x, n)
 *      i = i.succ
 *      f = f.mult(i, n)
 *    end
 *  
 *    case func
 *    when :sin
 *      sin.round(prec)
 *    when :cos
 *      cos.round(prec)
 *    when :sincos
 *      [sin.round(prec), cos.round(prec)]
 *    when :tan
 *      sin.round(prec).div(cos.round(prec), prec)
 *    when :csc
 *      BigDecimal(1).div(sin, prec)
 *    when :sec
 *      BigDecimal(1).div(cos, prec)
 *    when :cot
 *      cos.round(prec).div(sin.round(prec), prec)
 *    end
 *  end
 *  ```
 * 
 * In this Ruby code, you can create the value of the entire trigonometric 
 * function. In C code, you need to be more aware of function procedures.
 */
static void
sincos_inline(VALUE x, VALUE prec, VALUE *sin, VALUE *cos)
{
	const ID div = rb_intern("div");
	VALUE n, m, f, w, a, y;
	long i = 0;
	
	n = rb_numdiff_make_n(prec);
	f = BIG_ONE;
	w = BIG_ONE;
	a = BIG_ONE;
	y = BIG_ZERO;
	if (sin != NULL)  *sin = BIG_ZERO;
	if (cos != NULL)  *cos = BIG_ZERO;
	while (rb_numdiff_condition_p(y, a, n, &m))
	{
		a = rb_funcall(w, div, 2, f, m);
		switch (i % 4) {
		case 0:
			if (cos != NULL) *cos = (y = rb_funcall1(*cos, '+', a));
			break;
		case 1:
			if (sin != NULL) *sin = (y = rb_funcall1(*sin, '+', a));
			break;
		case 2:
                        if (cos != NULL) *cos = (y = rb_funcall1(*cos, '-', a));
			break;
		case 3:
                        if (sin != NULL) *sin = (y = rb_funcall1(*sin, '-', a));
			break;
		}
		w = rb_funcall1(w, '*', x);
		f = rb_funcall1(f, '*', LONG2NUM(++i));
	}
	RB_GC_GUARD(f);
	RB_GC_GUARD(w);
	RB_GC_GUARD(a);
	RB_GC_GUARD(y);
	if (sin != NULL)  RB_GC_GUARD(*sin);
	if (cos != NULL)  RB_GC_GUARD(*cos);
}

void
sincos_ser(VALUE x, VALUE prec, VALUE *sin, VALUE *cos)
{
	VALUE pi, t, y;
	
	if (sin == NULL && cos == NULL)
		return;
	
	if (!rb_num_finite_p(x))
	{
		if (sin != NULL)  *sin = BIG_NAN;
		if (cos != NULL)  *cos = BIG_NAN;
		return;
	}
	pi = rb_bigmath_const_pi(prec);
	y = sincos_to_radian(x, prec, pi, &t);
	if (degree_sparg(t, prec, sin, cos) == -1)
		sincos_inline(y, prec, sin, cos);
}
