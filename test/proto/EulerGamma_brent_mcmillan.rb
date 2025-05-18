require './lib/bigdecimal/math_r'

require 'bigdecimal'
require 'bigdecimal/util'

# FIXME: 1.288761308183e-38分の誤差が出る
def euler_gamma(prec)
  raise TypeError, "precision must be in Integer" unless prec.class == Integer
  raise RangeError, "Zero or negative precision" if prec <= 0
  n = BigDecimal(prec + BigDecimal.double_fig)


test_v = BigMathR::Const::EulerGamma.engel(n.to_i)

  one = BigDecimal(1)

  a = u = -BigMathR.log(n, n.to_i)
  b = v = one

  i = one
  loop do

p u.div(v, n).sub(test_v, n).to_f

    k = (n / i) * (n / i)
    b *= k
    v1 = v.add(b, n.to_i)
    break if v1 == v
    a = (a.mult(k, n)) + (b.div(i, n))
    u += a
    v = v1
    i = i + one
  end

  u.div(v, prec)
end


