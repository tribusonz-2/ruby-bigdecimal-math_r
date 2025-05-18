# frozen_string_literal: true

require './lib/bigdecimal/math_r'
require 'benchmark'

module BigMath

  module_function

  def gamma(x, prec)
    raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
    raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0

    x = x.to_d(prec) unless x.class == BigDecimal

    # Factorial Function
    factorial = lambda do
      return 1 if x == 0
      return BigDecimal::INFINITY if x.negative?
      (1..x).inject(1){|product, i| product * i}
    end

    # Loggamma Routine  (Reference: Haruhiko Okumura: C-gengo ni yoru hyoujun algorithm jiten)
    loggamma = lambda do
      log_2pi = log(PI(prec) * 2, prec)  # $\log 2\pi$ 
      n = 8
      coef = [
           1/12r,     # B_2  / ( 2 *  1) =     1/12
          -1/360r,    # B_4  / ( 4 *  3) =    -1/360
           1/1260r,   # B_6  / ( 6 *  5) =     1/1260
          -1/1680r,   # B_8  / ( 8 *  7) =    -1/1680
           1/1188r,   # B_10 / (10 *  9) =     1/1188
        -691/360360r, # B_12 / (12 * 11) =  -691/360360
           1/156r,    # B_14 / (14 * 13) =     1/156
       -3617/122400r  # B_16 / (16 * 15) = -3617/122400
      ]
      v = 1
      while (x < n);  v *= x;  x += 1;  end
      w = 1 / (x * x)

      y =  (((((((coef[7]  * w + coef[6]) * w + coef[5]) * w + coef[4]) * w\
                + coef[3]) * w + coef[2]) * w + coef[1]) * w + coef[0]) / x\
                + 0.5 * log_2pi - log(v, prec) - x + (x - 0.5) * log(x, prec)
      y
    end

    # Positive Argument Routine
    positive = lambda do
      y = loggamma.call
      exp(y, prec)
    end

    # Negative Argument Routine FIXME: Bad calculation
    negative = lambda do
      s = sin(PI(prec) * x, prec)
      x = 1 - x
      PI(prec) / s * exp(positive.call, prec)
    end

    case x
    when BigDecimal::NAN
      BigDecimal::NAN
    when BigDecimal::INFINITY
      x.negative? ? BigDecimal::NAN : BigDecimal::INFINITY
    when BigDecimal('0')
      BigDecimal::INFINITY
    else # BigDecimal # Finite
      if x.frac == 0
        x = x.to_i - 1
        factorial.call
      else
        y = x.negative? ? negative.call : positive.call
#        y.round(prec)
      end
    end
  end
end


N = 10000
PREC = 20

  Benchmark.bm(20) do |x|
    x.report(">>> gamma(1.5)") { for i in 1..N; BigMath.gamma(BigDecimal('-0.45'), PREC); end }
  end
