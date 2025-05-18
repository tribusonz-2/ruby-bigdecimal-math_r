# frozen_string_literal: true

require 'bigdecimal'

def atan_fib(x, prec)
  raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
  raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0
  n = BigDecimal.double_fig + prec
  one = BigDecimal(1)
  two = BigDecimal(2)
  five = BigDecimal(5)

  d = one
  y = BigDecimal(0)

  fib1 = one
  fib2 = BigDecimal(0)
  t = (two * x) / (one + (one + ((BigDecimal(4) * x * x) / five)).sqrt(n))
  t2 = t * t
  i = one

  while d.nonzero? && ((m = n - (y.exponent - d.exponent).abs) > 0)
    m = BigDecimal.double_fig if m < BigDecimal.double_fig
    y = y + d
    d /= five
    i = i + two; d /= i
    t = t.mult(t2, m); d = d.mult(t, m)
    2.times { fib1 += fib2; fib2 = fib1 - fib2 }
    d *= fib1;
    d = -d
  end
  y.round(prec)

end
