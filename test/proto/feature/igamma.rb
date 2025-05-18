# frozen_string_literal: true

require 'bigdecimal/math'
require './math_r'

def p_gamma(a, x, loggamma_a, prec)
  zero = BigDecimal(0)
  one = BigDecimal(1)
  return one - q_gamma(a, x, loggamma_a, prec) if (x >= one + a)
  return zero if x.zero?
  n = BigDecimal.double_fig + prec
  result = term = BigMathR::EDF.exp(a * BigMathR.log(x, n) - x - loggamma_a, n) / a
  for k in 1..1000 do
    term *= x / (a + BigDecimal(k))
    previous = result; result = result.add(term, n)
    return result if (result == previous)
  end
  warn "p_gamma(): can't converge."
  return result
end

def q_gamma(a, x, loggamma_a, prec)
  one = BigDecimal(1)
  return one - p_gamma(a, x, loggamma_a, prec) if (x < one + a)
  n = BigDecimal.double_fig + prec
  la = one; lb = one + x - a;  # Laguerreの多項式
  w = BigMathR::EDF.exp(a * BigMath.log(x, prec) - x - loggamma_a, n);
  result = w / lb
  for k in 2..1000 do
    temp = ((BigDecimal(k) - one - a) * (lb - la) + (BigDecimal(k) + x) * lb).div(BigDecimal(k), n);
    la = lb;  lb = temp;
    w *= (BigDecimal(k) - one - a) / BigDecimal(k);
    temp = w / (la * lb);
    previous = result;  result = result.add(temp, n);
    return result if (result == previous)
  end
  warn "q_gamma(): can't converge."
  return result
end


def LOG_PI(prec)
  BigMath.log(BigMath.PI(prec), prec)
end

# Gaussの誤差関数 ${\rm erf}(x)$
def erf(x, prec)
  n = prec + BigDecimal.double_fig
  log_pi = BigMath.log(BigMath.PI(n), n)
  half = BigDecimal('0.5')
  two = BigDecimal(2)
  y = if (x >= 0)
    p_gamma(half, x * x, log_pi.div(two, n), prec)
  else
    -p_gamma(half, x * x, log_pi.div(two, n), prec)
  end
  y.round(prec)
end

# $1 - {\rm erf}(x)$
def erfc(x, prec)
  n = prec + BigDecimal.double_fig
  log_pi = BigMath.log(BigMath.PI(n), n)
  half = BigDecimal('0.5')
  two = BigDecimal(2)
  y = if (x >= 0)
    q_gamma(half, x * x, log_pi.div(two, n), prec)
  else
    1 + p_gamma(half, x * x, log_pi.div(two, n), prec)
  end
  y.round(prec)
end
