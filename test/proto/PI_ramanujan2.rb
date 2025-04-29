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
        r = 1123/882r

        d = BigDecimal(1)
        y = BigDecimal(0)

        while d.nonzero? && ((m = n - (y.exponent - d.exponent).abs) > 0)
          m = BigDecimal.double_fig if m < BigDecimal.double_fig
          d = BigDecimal(r, m)
          y = y + d
          i = i.succ
          r *= -21460
          r *= 16 * i * i * i - 20 * i * i + 8 * i - 1
          r /= 777924
          r /= 32
          3.times { r /= i }
        end
        BigDecimal(4).div(y, prec)
      end
    end
  end
end

