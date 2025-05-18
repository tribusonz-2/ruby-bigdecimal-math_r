#/***********************************************************
#    zeta.rb -- Riemannのゼータ関数
#***********************************************************/

require 'bigdecimal/util'

def bernoulli_list(_N)
  raise ArgumentError, "argument N must be Integer" unless _N.class == Integer
  raise RangeError, "negative number" if _N.negative?

  b_n = Hash.new
  b_n[0] = 1/1r
  b_n[1] = -1/2r

  t = []
  (_N+1).times { t.push(0) }
  q = 1
  t[1] = 1
  for n in 2.._N
    for i in 1...n; t[i - 1] = i * t[i]; end
    t[n - 1] = 0
    n.downto(2) {|i| t[i] += t[i - 2] }
    if (n % 2 == 0) 
      q *= 4
      b1 = n * t[0];  b2 = q * (q - 1)
      r = n % 4 == 0 ? Rational(-b1, b2) : Rational(b1, b2)
      b_n[n] = r
    end
  end
  b_n
end

def factorial_list(_N)
  raise ArgumentError, "argument N must be Integer" unless _N.class == Integer
  raise RangeError, "negative number" if _N.negative?

  f_n = Hash.new
  f_n[0] = 1

  (1.._N).inject(1) { |product, i| f_n[i] = product * i }

  f_n
end

# SEKI takakazu's Hoen B_n/n!
def hoen_list(_N)
  raise ArgumentError, "argument N must be Integer" unless _N.class == Integer
  raise RangeError, "negative number" if _N.negative?

  b_n = bernoulli_list(_N)
  f_n = factorial_list(_N)
  h_n = Hash.new

  for n in 2.._N
    if b_n.key?(n)
      h_n[n] = b_n[n]/f_n[n]
    end
  end

  h_n
end

$HOEN = nil

def riemann_zeta_summation(x, prec)
  raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
  raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0

  n = BigDecimal.double_fig + prec
  _N = n / 2

  zprev = 0

  x = x.to_d unless x.class == BigDecimal

  $HOEN = hoen_list(n) if $HOEN.nil? or $HOEN[n].nil?

  z = BigDecimal(1)
  for i in 2..._N
    zprev = z
    z += BigDecimal(i).power(-x, n)
    if (z == zprev); return z.round(prec); end
  end
  powNx = BigDecimal(_N).power(x, n)
  w = x / (_N * powNx)
  z += 0.5 / powNx + _N / ((x - 1) * powNx) + $HOEN[2] * w

  i = 1
  while (i < _N && z != zprev)
    t = x + 2 * i
    w *= (t - 1) * t / (_N * _N)
    zprev = z
    z += $HOEN[2*i+2] * w
    i = i.succ
  end
  return z.round(prec)
end

printf("Riemannのゼータ関数\n")
for x in 2..20
    printf("zeta(%2.0f) = %s\n", x, riemann_zeta_summation(x, 33))
end
