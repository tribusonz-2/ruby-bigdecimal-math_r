# frozen_string_literal: true

require 'bigdecimal/math'

module BigMathR
  module Const
    module PI
      module_function
      def PI_euler(prec)
        raise ArgumentError, "Zero or negative precision for PI" if prec <= 0
        one = BigDecimal(1)
        two = BigDecimal(2)
        s = BigDecimal(0)
        t = one
        t1 = BigDecimal(0)
        t2 = one
        n = prec + BigDecimal.double_fig
        while t.nonzero? && ((m = n - (s.exponent - t.exponent).abs) > 0)
          m = BigDecimal.double_fig if m < BigDecimal.double_fig
          s = s + t
          t1 = t1 + one;  t = t.mult(t1, m)
          t2 = t2 + two;  t = t.div(t2, m)
        end
        two.mult(s, prec)
      end
    end
  end
end

