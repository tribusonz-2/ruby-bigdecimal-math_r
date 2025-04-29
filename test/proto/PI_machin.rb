# frozen_string_literal: true

require 'bigdecimal/math'

module BigMathR
  module Const
    module PI
      module_function
      def machin(prec)
        raise ArgumentError, "Zero or negative precision for PI" if prec <= 0
        one = BigDecimal(1)
        two = BigDecimal(2)
        m25 = BigDecimal('-0.04')
        m57121 = BigDecimal('-57121')
        m = prec + BigDecimal.double_fig
        pi = BigDecimal(0)
        k = one
        t = BigDecimal(16/5r, m)
        loop do
          pi = pi + t.div(k, m)
          t = t * m25
          k = k+two
          break if (t.exponent + m) < 0
        end
        k = one
        t = BigDecimal(4/239r, m)
        loop do
          pi = pi - t.div(k, m)
          t = t.div(m57121, m)
          k = k+two
          break if (t.exponent + m) < 0
        end
        pi.round(prec)
      end
    end
  end
end
