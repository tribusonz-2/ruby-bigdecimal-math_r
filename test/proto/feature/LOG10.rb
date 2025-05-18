# frozen_string_literal: true

# @see https://mathworld.wolfram.com/NaturalLogarithmof10.html

require 'bigdecimal'

def LOG10_atanh(prec)
  raise TypeError, "precision must be in Integer" unless prec.class == Integer
  raise RangeError, "Zero or negative precision" if prec <= 0
  n = BigDecimal.double_fig + prec
  
  zero = BigDecimal(0)
  one  = BigDecimal(1)
  two  = BigDecimal(2)
  
  k = one
  x = BigDecimal(9/11r, n)
  x2 = BigDecimal(81/121r, n) # (9/11)^2
  d = one
  y = zero
  while d.nonzero? && ((m = n - (y.exponent - d.exponent).abs) > 0)
    m = BigDecimal.double_fig if m < BigDecimal.double_fig
    d = x.div(k, m)
    y = y + d
    x = x.mult(x2, n)
    k = k + two
  end
  y.mult(BigDecimal(2), prec)
end


# error = -0.6373290825e-39
def LOG10_BBP(prec)
  raise TypeError, "precision must be in Integer" unless prec.class == Integer
  raise RangeError, "Zero or negative precision" if prec <= 0
  n = BigDecimal.double_fig + prec

  one_sixteen = BigDecimal(1/16r, n)
  zero = BigDecimal(0)
  one = BigDecimal(1)
  six = BigDecimal(6)
  twenty = BigDecimal(20)
  twentyfour = BigDecimal(24)

  k = zero
  d = one
  y = zero
  t1 = zero
  t2 = one
  while d.nonzero? && ((m = n - (y.exponent - d.exponent).abs) > 0)
    m = BigDecimal.double_fig if m < BigDecimal.double_fig
    t1 = [twentyfour, twenty, six, one].sum{|t| t / (k = k + one)}
    d = t1.mult(t2, m)
    y = y + d
    t2 *= one_sixteen
  end
  one_sixteen.mult(y, prec)
end


# \log10=-\log^\text{1p}(-\frac{9}{10})
