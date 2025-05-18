# frozen_string_literal: true

require 'bigdecimal/math'

# 級数展開
def Si_series(x, prec)
  n = BigDecimal.double_fig + prec
  s = t = x;  x = - x * x;
  3.step(1000, 2) do |k|
    t = t * x.div((k - 1) * k, n)
    d = t.div(k, n)
    s = s + d
    if (d.exponent + n) < 0
      return s.round(prec)
    end
  end

  puts("Si_series(): can't converge.")

  return s.round(prec)

end

# 漸近展開
def Si_asympt(x, prec)
  n = BigDecimal.double_fig + prec
  fmax = gmax = BigDecimal(2);  fmin = gmin = BigDecimal(0);
  f = g = BigDecimal(0);  t = BigDecimal(1) / x
  k = flag = 0;
  while (flag != 15)
    f += t;  t *= BigDecimal(k = k.succ) / x;
    if (f < fmax); fmax = f; else  flag |= 1  end
    g += t;  t *= BigDecimal(k = k.succ) / x;
    if (g < gmax); gmax = g; else  flag |= 2  end
    f -= t;  t *= BigDecimal(k = k.succ) / x;
    if (f > fmin); fmin = f; else  flag |= 4  end
    g -= t;  t *= BigDecimal(k = k.succ) / x;
    if (g > gmin); gmin = g; else  flag |= 8  end
  end
  pi = BigMath.PI(n)
  y = 1/2r * (pi - (fmax + fmin).mult(BigMath.cos(x, n), n)\
                - (gmax + gmin).mult(BigMath.sin(x, n), n))
  y.round(prec)
end

def Si(x, prec)
  if (x <  0); return -Si(-x, prec) end
  if (x < 18); return  Si_series(x, prec) end
  return               Si_asympt(x, prec)
end

# 
# #include <stdlib.h>
# 
# int main(void)
# {
#     double x;
# 
#     printf(" x     Si(x)\n");
#     for (x = 1; x <= 50; x++)
#         printf("%2.0f  %.10f\n", x, Si(x));
#     return 0;
# }

