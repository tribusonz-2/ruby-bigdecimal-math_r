# frozen_string_literal: true

require 'bigdecimal/math'

module BigMathR
  module Const
    module LOG2
      module_function
      def bbp2002(prec)
        raise TypeError, "precision must be in Integer" unless prec.class == Integer
        raise RangeError, "Zero or negative precision" if prec <= 0
        n = BigDecimal.double_fig + prec

        zero = BigDecimal(0)
        one  = BigDecimal(1)
        two  = BigDecimal(2)
        nine = BigDecimal(9)

        a = one
        r = one
        d = one
        y = zero

        while d.nonzero? && ((m = n - (y.exponent - d.exponent).abs) > 0)
          m = BigDecimal.double_fig if m < BigDecimal.double_fig
          d = r.div(a, m)
          y += d
          a += two
          r = r.div(nine, n)
         end
        y.mult(2/3r, prec)
      end
    end
  end
end
