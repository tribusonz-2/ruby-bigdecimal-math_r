# frozen_string_literal: true

require 'bigdecimal/math'

module BigMathR
  module Const
    module PI
      module_function
      def ramanujan1(prec)
        raise TypeError, "precision must be in Integer" unless prec.class == Integer
        raise RangeError, "Zero or negative precision" if prec <= 0
        n = BigDecimal.double_fig + prec
        zero = BigDecimal(0)
        one = BigDecimal(1)
        p26390 = BigDecimal(26390)
        p24591257856 = BigDecimal(1/24591257856r, n)
      
        pi = zero
        y = zero
        i = zero
      
        rat_m1 = one
        rat_m2 = BigDecimal(1103)
        rat_m3 = one
        rat_n = one
      
        fac1 = one
        fac4 = zero
      
        d = one
      
        while d.nonzero? && ((m = n - (y.exponent - d.exponent).abs) > 0)
          m = BigDecimal.double_fig if m < BigDecimal.double_fig
          d = (rat_m1 * rat_m2 * rat_m3).div(rat_n, m)
          y += d
          rat_m1 *= p24591257856 # 24591257856^-n
          rat_m2 += p26390 # 26390n + 1103
          4.times {rat_m3 *= fac4 += one} # (4n)!
          fac1 *= (i = i + one)
          rat_n = 4.times.inject(1){|s, _| s * fac1} # (n!)^4
        end
        
        pi = ((BigDecimal(8).sqrt(n)) / 9801) * y
        pi = one.div(pi, n)
      
        
        pi.round(prec)
      end
    end
  end
end
