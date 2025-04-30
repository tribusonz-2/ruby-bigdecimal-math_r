# frozen_string_literal: true

require 'bigdecimal/math'

module BigMathR
  module Const
    module PI
      module_function
      def ramanujan2(prec)
        raise TypeError, "precision must be in Integer" unless prec.class == Integer
        raise RangeError, "Zero or negative precision" if prec <= 0
        n = BigDecimal.double_fig + prec

        i = 0
        r = 1/882r
        k = 1123

        d = BigDecimal(1)
        y = BigDecimal(0)

        while d.nonzero? && ((m = n - (y.exponent - d.exponent).abs) > 0)
          m = BigDecimal.double_fig if m < BigDecimal.double_fig
          d = BigDecimal(r * k, m)
          y = y + d
          i = i.succ
          k += 21460
          r = -r
          r *= 32 * i * i * i - 48 * i * i + 22 * i - 3
          r /= 777924
          r /= 32
          3.times { r /= i }
        end
        BigDecimal(4).div(y, prec)
      end
    end
  end
end
