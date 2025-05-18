

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

int
rb_bigmath_degree_sparg(VALUE t, VALUE prec, VALUE *sin, VALUE *cos)
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
