require 'bigdecimal/math'

def LOG_PI_builtin(prec)
  BigMath.log(BigMath.PI(prec), prec)
end

def LOG_PI_ser(prec)
  raise ArgumentError, "Zero or negative precision for PI" if prec <= 0
  one = BigDecimal(1)
  two = BigDecimal(2)

  x = one - two / (BigMath.PI(prec) + one)
  x2 = x * x
  t = one
  d = one
  y = BigDecimal(0)

  n = prec + BigDecimal.double_fig

  while d.nonzero? && ((m = n - (y.exponent - d.exponent).abs) > 0)
    m = BigDecimal.double_fig if m < BigDecimal.double_fig
    d = x.div(t, m)
    y += d
    x = x.mult(x2, m)
    t += two
  end
  two.mult(y, prec)

end

