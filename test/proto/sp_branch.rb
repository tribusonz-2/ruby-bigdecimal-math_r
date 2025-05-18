# frozen_string_literal: true

require 'bigdecimal/math'

def erf_branch(x, prec)
  raise TypeError, "precision must be in Integer" unless prec.class == Integer
  raise RangeError, "Zero or negative precision" if prec <= 0
  return BigDecimal::NAN if x != x
  return BigDecimal(x < 0 ? -1 : 1) if x.infinite?
  absx = x.abs
  branch_condition_a = (BigDecimal(prec + 21) * BigMath.log(10, prec)).sqrt(prec).div(5, prec)
  if absx <= branch_condition_a
    y = erf_ser_zero(absx, prec)
    y = -y if x.negative?
    return y
  end
  branch_condition_b = (((prec + 6) * BigMath.log(10, prec)) ** 0.6r).div(4.1r, prec)
  if absx <= branch_condition_b
    y = erf_ser_inf(absx, prec)
    y = -y if x.negative?
    return y
  else
    y = erf_cf(absx, prec)
    y = -y if x.negative?
    return y
  end
end

def erf_ser_zero(x, prec)
  raise TypeError, "precision must be in Integer" unless prec.class == Integer
  raise RangeError, "Zero or negative precision" if prec <= 0
  n = BigDecimal.double_fig + prec

  zero = BigDecimal(0)
  one = BigDecimal(1)
  two = BigDecimal(2)

  x2 = x * x
  f = one
  r = one
  i = one
  d = x
  y = zero

  while d.nonzero? && ((m = n - (y.exponent - d.exponent).abs) > 0)
    m = BigDecimal.double_fig if m < BigDecimal.double_fig
    d = x.div(f * r, m)
    y = y + d
    x = -x.mult(x2, n)
    f *= i
    r += two
    i += one
  end
  (2 / BigMath.PI(prec).sqrt(prec)).mult(y.round(prec), prec)
end

def erf_ser_inf(x, prec)
  raise TypeError, "precision must be in Integer" unless prec.class == Integer
  raise RangeError, "Zero or negative precision" if prec <= 0
  n = BigDecimal.double_fig + prec

  s = BigMath.exp(-x * x, prec)
  return x.negative? ? BigDecimal(-1) : BigDecimal(1) if s.zero?
  s = s.div(BigMath.PI(prec).sqrt(prec), prec)

  zero = BigDecimal(0)
  one = BigDecimal(1)
  two = BigDecimal(2)

  x = two * x
  x2 = x * x
  f = one
  r = one
  i = zero
  i2 = one
  d = x
  y = zero

  while d.nonzero? && ((m = n - (y.exponent - d.exponent).abs) > 0)
    m = BigDecimal.double_fig if m < BigDecimal.double_fig
    d = (f * x).div(r, m)
    y = y + d
    x = x.mult(x2, n)
    f *= (i += one)
    r *= (i2 += one) * (i2 += one)
  end
  s.mult(y, prec)
end

def erf_cf(x, prec)
  raise TypeError, "precision must be in Integer" unless prec.class == Integer
  raise RangeError, "Zero or negative precision" if prec <= 0
  n = BigDecimal.double_fig + prec

  zero = BigDecimal(0)
  one = BigDecimal(1)

  c = -BigMath.exp(-x * x, prec)
  return x < 0 ? BigDecimal(-1) : BigDecimal(1) if c.round(prec).zero?
  c /= BigMath.PI(n).sqrt(n); b = x
  p1 = one;  q1 = zero;  p2 = one;  q2 = one;
  i = one
  loop do
    prev = p2
    t = p1 * c + p2 * b;  p1 = p2;  p2 = t;
    t = q1 * c + q2 * b;  q1 = q2;  q2 = t;
    if q2.nonzero?
      p1 = p1.div(q2, n);  q1 = q1.div(q2, n);  p2 = p2.div(q2, n);  q2 = one;
    end
    i += one
    c = i - one
    b = i % 2 == 1 ? x : 2 * x;
    break unless q2.nonzero? && prev != p2
  end
  (x < 0 ? -p2 : p2).round(prec)
end

def erfc_branch(x, prec)
  raise TypeError, "precision must be in Integer" unless prec.class == Integer
  raise RangeError, "Zero or negative precision" if prec <= 0
  return BigDecimal::NAN if x != x
  return BigDecimal(x < 0 ? 2 : 0) if x.infinite?
  branch_condition_a = (((prec + 6) * BigMath.log(10, prec)) ** 0.7).div(9, prec)
  if x <= branch_condition_a
    y = 1 - erf_branch(x, prec)
    return y;
  else
    y = erfc_cf(x, prec)
    return y;
  end
end

def erfc_cf(x, prec)
  raise TypeError, "precision must be in Integer" unless prec.class == Integer
  raise RangeError, "Zero or negative precision" if prec <= 0
  n = BigDecimal.double_fig + prec

  zero = BigDecimal(0)
  one = BigDecimal(1)

  c = BigMath.exp(-x * x, prec) / BigMath.PI(prec).sqrt(prec)
  return BigDecimal(0) if c.round(prec).zero?
  b = x
  p1 = one;  q1 = zero;  p2 = zero;  q2 = one;
  i = one
  loop do
    prev = p2
    t = p1 * c + p2 * b;  p1 = p2;  p2 = t;
    t = q1 * c + q2 * b;  q1 = q2;  q2 = t;
    if q2.nonzero?
      p1 = p1.div(q2, n);  q1 = q1.div(q2, n);  p2 = p2.div(q2, n);  q2 = one;
    end
    i += one
    c = i - one
    b = i % 2 == 1 ? x : 2 * x;
    break unless q2.nonzero? && prev != p2
  end
  p2.round(prec)
end
