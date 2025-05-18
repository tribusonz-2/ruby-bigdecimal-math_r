# frozen_string_literal: true

require 'bigdecimal'
require './math_r'

# Natural expansion algorithm (by Tomonori Kouya Ph.D)

def log_ser1(x, prec)
  raise TypeError, "precision must be in Integer" unless prec.class == Integer
  raise RangeError, "Zero or negative precision" if prec <= 0
  n = BigDecimal.double_fig + prec
  one = BigDecimal(1)
  x_2 = (x - one).div(x, n)
  w = x_2
  t = one
  y = BigDecimal(0)
  d = one
  while d.nonzero? && ((m = n - (y.exponent - d.exponent).abs) > 0)
    m = BigDecimal.double_fig if m < BigDecimal.double_fig
    d = w.div(t, m)
    y = y + d
    w *= x_2
    t = t + one
  end
  y.round(prec)
end

def log_ser2(x, prec)
  raise TypeError, "precision must be in Integer" unless prec.class == Integer
  raise RangeError, "Zero or negative precision" if prec <= 0
  n = BigDecimal.double_fig + prec
  one = BigDecimal(1)
  two = BigDecimal(2)
  x_2 = (x - one).div(x + one, n)
  w = x_2
  t = one
  y = BigDecimal(0)
  d = one
  while d.nonzero? && ((m = n - (y.exponent - d.exponent).abs) > 0)
    m = BigDecimal.double_fig if m < BigDecimal.double_fig
    d = w.div(t, m)
    y = y + d
    w *= x_2 * x_2
    t = t + two
  end
  y.mult(two, prec)
end

def logxt(x, t, prec)
  raise TypeError, "precision must be in Integer" unless prec.class == Integer
  raise RangeError, "Zero or negative precision" if prec <= 0
  n = BigDecimal.double_fig + prec

  a = Rational(x); b = BigDecimal(1); s = BigDecimal(0);
  p0_5 = BigDecimal('0.5')
  loop do
    a = (a * a).round(n);  b = p0_5 * b;
    if a >= t
      s = s + b; a = a / t; 
    end
    break unless (b.exponent + n) > 0
  end
  s.round(prec)
end


def log_p_adic(x, prec)
  raise TypeError, "precision must be in Integer" unless prec.class == Integer
  raise RangeError, "Zero or negative precision" if prec <= 0
  n = BigDecimal.double_fig + prec

  zero = BigDecimal(0)
  one = BigDecimal(1)

  t = x
  i = one
  d = one
  y = zero
  c = one
  while d.nonzero? && ((m = n - (y.exponent - d.exponent).abs) > 0)
    m = BigDecimal.double_fig if m < BigDecimal.double_fig

    d = (c * t).div(i, m)
    y = y + d
    c = -c
    i = i + one
    t *= x
  end
  y.round(prec)
end

def log_ser_okumura(x, prec)
  raise TypeError, "precision must be in Integer" unless prec.class == Integer
  raise RangeError, "Zero or negative precision" if prec <= 0
  
  return BigDecimal::NAN if x.negative?
  return -BigDecimal::INFINITY if x.zero?
  return BigDecimal(0) if x == 1
  return BigDecimal::INFINITY if x.infinite?

  n = BigDecimal.double_fig + prec
  
  one = BigDecimal(1)
  two = BigDecimal(2)
  
  # BUG: zŠÂ¬”‚¾‚ÆŒë·‚ðE‚¤‚±‚Æ‚ª‚ ‚éB
#  x = one.div(x, n) if inv = x > one
#  x = one / x if inv = x > one

  _, k = BigMathR::EDF.rcm2(x / BigMathR::PowerRoot.sqrt(2, prec))
  x /= BigMathR::EDF.integer_power(2, k = k.succ, n)
  x = (x - one) / (x + one)
  x2 = x * x
  i = one
  s = x
  d = BigDecimal(1)

  while d.nonzero? && ((m = n - (s.exponent - d.exponent).abs) > 0)
    m = BigDecimal.double_fig if m < BigDecimal.double_fig
    
    x = x.mult(x2, m)
    i = i + two
    d = x.div(i, m)
    s += d
  end

  y = (BigMathR.LOG2(n) * k).add(2 * s, prec)
#  inv ? -y : y
end


def test(x, prec)
  puts "x = #{x}"
  puts "PREC = #{prec}"
  puts "log_ser1(x) = #{log_ser1(x, prec)}"
  puts " DIFF = #{log_ser1(x, prec) - BigMath.log(x, prec).round(prec)}"
  puts "log_ser2(x) = #{log_ser2(x, prec)}"
  puts " DIFF = #{log_ser2(x, prec) - BigMath.log(x, prec).round(prec)}"
  puts "log_okumura_ser(x) = #{log_ser_okumura(x, prec)}"
  puts " DIFF = #{log_ser_okumura(x, prec) - BigMath.log(x, prec).round(prec)}"

  puts
end

def main
  prec = 100
  test(BigDecimal(2), prec)
  test(BigDecimal('1.5'), prec)
end

# main

#=> x = 0.2e1
#=> PREC = 100
#=> log_ser1(x) = 0.6931471805599453094172321214581765680755001343602552541206800094933936219696947156058633269964186875e0
#=>  DIFF = 0.0
#=> log_ser2(x) = 0.6931471805599453094172321214581765680755001343602552541206800094933936219696947156058633269964186875e0
#=>  DIFF = 0.0
#=> 
#=> x = 0.15e1
#=> PREC = 100
#=> log_ser1(x) = 0.4054651081081643819780131154643491365719904234624941976140143241441006712489142512677524278173134012e0
#=>  DIFF = 0.0
#=> log_ser2(x) = 0.4054651081081643819780131154643491365719904234624941976140143241441006712489142512677524278173134012e0
#=>  DIFF = 0.0


# require './test/proto/LOG2_bbp2002'
# require './test/proto/feature/log'
# 
# def LOG10(prec)
#   log2 = BigMathR::Const::LOG2.bbp2002(prec)
#   fra = log_p_adic(0.625r, prec)
#   (log2 * 4).add(fra, prec)
# end
# 
# 
# LOG10(100)
