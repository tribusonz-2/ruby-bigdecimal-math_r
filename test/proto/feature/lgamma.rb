# frozen_string_literal: true

require 'bigdecimal/math'

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


def lgamma_denom_list(_N)
  raise ArgumentError, "argument N must be Integer" unless _N.class == Integer
  raise RangeError, "negative number" if _N.negative?

  lgam_denom_coef_n = Hash.new

  (2.._N).step(2) { |i| lgam_denom_coef_n[i] = i * (i - 1) }

  lgam_denom_coef_n
end

def lgamma_coef_list(_N)
  raise ArgumentError, "argument N must be Integer" unless _N.class == Integer
  raise RangeError, "negative number" if _N.negative?

  b_n = bernoulli_list(_N)
  g_n = lgamma_denom_list(_N)
  h_n = Hash.new

  for n in 2.._N
    if b_n.key?(n)
      h_n[n] = b_n[n]/g_n[n]
    end
  end

  h_n
end


$LGAMMA_COEF = nil

N = 8

def lgamma(x, prec)
  raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
  raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0

  n = BigDecimal.double_fig + prec

  x = x.to_d(prec) unless x.class == BigDecimal

  return BigDecimal('0', n) if x == 1 or x == 2

  # Positive Argument Routine  (Reference: Haruhiko Okumura: C-gengo ni yoru hyoujun algorithm jiten)
  positive = lambda do
    log_2pi = BigMath.log(BigMath.PI(n) * 2, n)  # $\log 2\pi$ 

    $LGAMMA_COEF = lgamma_coef_list(n) if $LGAMMA_COEF.nil? or $LGAMMA_COEF[n].nil?

    v = 1
    while (x < N);  v *= x;  x += 1;  end
    w = 1 / (x * x)
    y = ((n)..2).step(-2).inject($LGAMMA_COEF[n]) {|s, n| s * w + $LGAMMA_COEF[n] }
    y = y / x + 0.5 * log_2pi - BigMath.log(v, n) - x + (x - 0.5) * BigMath.log(x, n)
    y
  end
    
  # Negative Argument Routine
  negative = lambda do
    s = BigMath.sin(BigMath.PI(n) * x, n)
    [s.round(n)].each {|s1| return 1 / s1 if s1.zero?}
    s = (1 / s).abs

    x = 1 - x
    y = BigMath.log(s, n) - positive.call + BigMath.log(BigMath.PI(n), n)
    y
  end

  case x
  when BigDecimal::NAN
    BigDecimal::NAN
  when BigDecimal::INFINITY
    x.negative? ? BigDecimal::NAN : BigDecimal::INFINITY
  when BigDecimal('0')
    BigDecimal::INFINITY
  else # BigDecimal # Finite
    y = x.negative? ? negative.call : positive.call
    y.round(prec - y.exponent)
  end
end
