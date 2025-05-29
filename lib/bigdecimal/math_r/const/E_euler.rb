# frozen_string_literal: true

module BigMathR
  module Const
    module E
      module_function
      # Implement by continued fraction.
      # 
      # @example
      #  BigMathR::Const::E.euler(20)
      #  #=> 0.271828182845904523536e1
      # @param prec [Integer] Arbitrary precision
      # @return [BigDecimal] Constant e.
      # @raise [TypeError] not an Integer
      # @raise [RangeError] Zero or negative precision
      def euler(prec)
        raise TypeError, "precision must be in Integer" unless prec.class == Integer
        raise RangeError, "Zero or negative precision" if prec <= 0
        n = BigDecimal.double_fig + prec

        zero = BigDecimal(0)
        one = BigDecimal(1)
        two = BigDecimal(2)

        c = one
        b = one
        p1 = one;  q1 = zero;  p2 = two;  q2 = one;
        i = one
        loop do
          prev = p2
          t = p1 * c + p2 * b;  p1 = p2;  p2 = t;
          t = q1 * c + q2 * b;  q1 = q2;  q2 = t;
          if q2.nonzero?
            p1 = p1.div(q2, n);  q1 = q1.div(q2, n);  p2 = p2.div(q2, n);  q2 = one;
          end
          i += one
          c = one
          b = (i + one) % 3 == 0 ? ((i.to_i.succ) / 3) * two : one
          break unless q2.nonzero? && prev != p2
        end
        p2.round(prec)
      end
    end
  end
end

