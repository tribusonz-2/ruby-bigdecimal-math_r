# frozen_string_literal: true

require 'bigdecimal/math'

# A003031: https://oeis.org/A003031
# 0 <= |x| <= S(sqrt(2))
def fresnel_s(z, prec)
  fac = 1
  n = 0
  pi = BigMath.PI(prec)
  phi = pi
  s = BigDecimal(0)
  z4 = -(z * z * z * z)
  w = 1
  nth = 3
  twopower_x = -1
  loop do
    if n != 0
      fac *= (2 * n) * (2 * n + 1)
      nth += 4
      twopower_x -= 2
    end
    a = Rational(2 ** twopower_x, (fac * nth))
    a = BigDecimal(a, prec)
    s += (b = a * phi * w)
    break if b.zero? or b.exponent < -prec
    phi *= pi * pi
    w *= z4
    n += 1
  end

  (z * z * z * s).round(prec)
end


# (1+2k)! = k=0: 1, k=1: 6, k=2: 120, k=3: 5040, ...
