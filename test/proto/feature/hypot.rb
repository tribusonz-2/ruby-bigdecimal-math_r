require 'bigdecimal'

# Moler-Morrison Method
def hypot_mmm(x, y, prec)
  raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
  raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0
  n = BigDecimal.double_fig + prec

  two = BigDecimal(2)
  four = BigDecimal(4)

  t = BigDecimal(1)
  x = x.abs; y = y.abs
  if x < y
    t = x;  x = y;  y = t; 
  end
  return x if y.zero?
  while t.nonzero? && ((m = n - (x.exponent - t.exponent).abs) > 0)
    m = BigDecimal.double_fig if m < BigDecimal.double_fig
    t = y.div(x, m);
    t = t.mult(t, m);
    t /= four + t;
    x += two * x * t;
    y *= t;
  end
  x.round(prec)
end

def hypot_formula(x, y, prec)
  raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
  raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0
  (x * x + y * y).sqrt(prec)
end
