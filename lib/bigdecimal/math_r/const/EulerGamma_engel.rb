# frozen_string_literal: true

require 'bigdecimal'

module BigMathR
  module Const
    module EulerGamma
      module_function
      # Implement by Engel expansion.
      # 
      # @example
      #  BigMathR::Const::EulerGamma.engel(20)
      #  #=> 0.57721566490153286061e0
      # @param prec [Integer] Arbitrary precision
      # @return [BigDecimal] Euler-Mascheroni constant gamma
      # @raise [TypeError] not an Integer
      # @raise [RangeError] Zero or negative precision
      # @see https://oeis.org/A053977
      def engel(prec)
        raise TypeError, "precision must be an Integer" unless prec.class == Integer
        raise RangeError, "Zero or negative precision" if prec <= 0
        n = BigDecimal.double_fig + prec

        f = File.open(__dir__ + '/b053977/b053977.txt', 'r')
        g = 1
        fread = -> do
          raise "there is no more list" if f.eof?
          _, coef = f.readline.chomp.split(' ');
          raise "expansion maximum reached" if coef.nil?
          g *= coef.to_i
        end

        d = BigDecimal(1)
        y = BigDecimal(0)

        while d.nonzero? && ((m = n - (y.exponent - d.exponent).abs) > 0)
          m = BigDecimal.double_fig if m < BigDecimal.double_fig
          d = BigDecimal(Rational(1, fread.call), m)
          y += d
        end
        y.round(prec)
      end
    end
  end
end

