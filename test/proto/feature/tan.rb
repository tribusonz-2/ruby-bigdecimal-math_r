require 'bigdecimal/math'

def ur_tan(x, prec)
  n = BigDecimal.double_fig + prec
  n = n.succ if n.even?
  p3217_2048 = BigDecimal(3217/2048r, 20)
  pi = BigMath.PI(n)
  d = (BigDecimal(3217) - BigDecimal(1024) * pi) / BigDecimal(2048)
  k = (x / (pi / 2) + (x >= 0 ? 0.5 : -0.5)).to_i
  x = +(x - p3217_2048 * BigDecimal(k)) + d * BigDecimal(k)
  x2 = x * x
  t = 0
  i = n
  n.step(3, -2) {|i| t = x2.div(i - t, n)}
  [x.div(1 - t, prec), k]
end

def tan(x, prec)
  t, k = ur_tan(x, prec)
  return t if k.even?
  return BigDecimal(-1).div(t, prec) if t != 0
  BigDecimal::INFINITY
end

def sin(x, prec)
  t, k = ur_tan(x / 2, prec)
  t = 2 * t / (1 + t * t); t = t.round(prec)
  return  t if k.even?
  return -t # else
end

def cos(x, prec)
  sin(BigMath.PI(prec) / 2 - x.abs, prec)
end

