# frozen_string_literal: true

require 'bigdecimal/math'

module BigMathR
  module Const
    module PI
      module_function
      # Implement by Euler's formula.
      # 
      # @example
      #  BigMathR::Const::PI.euler(20)
      #  #=> 0.31415926535897932385e1
      # @param prec [Integer] Arbitrary precision
      # @return [BigDecimal] Constant PI
      # @raise [TypeError] not an Integer
      # @raise [RangeError] Zero or negative precision
      def euler(prec)
        raise TypeError, "precision must be an Integer" unless prec.class == Integer
        raise RangeError, "Zero or negative precision" if prec <= 0
        n = BigDecimal.double_fig + prec
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

