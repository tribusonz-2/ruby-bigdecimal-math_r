# frozen_string_literal: true

require 'bigdecimal/math'

module BigMathR
  module Const
    module PI
      module_function
      # Implement by Chudnovsky's formula
      # 
      # @example
      #  BigMathR::Const::PI.chudnovsky(20)
      #  #=> 0.31415926535897932385e1
      # @param prec [Integer] Arbitrary precision
      # @return [BigDecimal] Constant PI
      # @raise [TypeError] not an Integer
      # @raise [RangeError] Zero or negative precision
      def chudnovsky(prec)
        raise TypeError, "precision must be an Integer" unless prec.class == Integer
        raise RangeError, "Zero or negative precision" if prec <= 0

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
