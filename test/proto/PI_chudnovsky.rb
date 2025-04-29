# frozen_string_literal: true

require 'bigdecimal/math'

# Chudnovsky's formula.
# If the number of digits is about 100, # fast convergence can be expected, 
# but since one derivative is nearly 11 digits, # the larger the accuracy, the slower the convergence.
# Machin's formula may be the fastest.
# If you change the calculation algorithm (e.g., calculate everything with the BigDecimal class), it may be faster.

module BigMathR
  module Const
    module PI
      module_function
      def chudnovsky(prec)
        raise ArgumentError, "Zero or negative precision for PI" if prec <= 0

        zero = BigDecimal(0)
        one = BigDecimal(1)

        n = prec + BigDecimal.double_fig

        m1_640320_3 = BigDecimal(-1/262537412640768000r, n)
        p90856689_711822400 = BigDecimal(90856689/711822400r, n)
        p90856689_711822400 *= BigDecimal(10005).sqrt(n)

        _C = one
        _AB = BigDecimal(13591409/545140134r, n)
        _F = 1r

        d = one
        y = zero

        i = 0

        while d.nonzero? && ((m = n - (y.exponent - d.exponent).abs) > 0)
          m = BigDecimal.double_fig if m < BigDecimal.double_fig

          d = BigDecimal(_F, m).mult(_AB * _C, m)
          y = y + d

          _AB += one
          _C *= m1_640320_3
          i = i.succ
          (6 * i - 5).step(6 * i) {|k| _F *= k}
          (3 * i - 2).step(3 * i) {|k| _F /= k}
          3.times { _F /= i }
        end
        
        y = y.mult(p90856689_711822400, n)
        one.div(y, prec)
      end
    end
  end
end
