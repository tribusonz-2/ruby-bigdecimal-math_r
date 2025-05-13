# frozen_string_literal: true

module BigMathR
  module Const
    module LOG2
      module_function
      # Implement by BBP's formula (Bailey et al. 2007)
      # 
      # @example
      #  BigMathR::Const::LOG2.bbp2007(20)
      #  #=> 0.69314718055994530942e0
      # @param prec [Integer] Arbitrary precision
      # @return [BigDecimal] Natural logarithm of 2
      # @raise [TypeError] not an Integer
      # @raise [RangeError] Zero or negative precision
      def bbp2007(prec)
        raise TypeError, "precision must be an Integer" unless prec.class == Integer
        raise RangeError, "Zero or negative precision" if prec <= 0

        n = prec + BigDecimal.double_fig
        one = BigDecimal(1)
        two = BigDecimal(2)
        i1 = one
        i2 = two
        d = one
        y = BigDecimal(0)

        while d.nonzero? && ((m = n - (y.exponent - d.exponent).abs) > 0)
          m = BigDecimal.double_fig if m < BigDecimal.double_fig
          d = one.div(i1 * i2, m)
          y = y + d
          i1 += one
          i2 *= two
        end
        y.round(prec)
      end
    end
  end
end
