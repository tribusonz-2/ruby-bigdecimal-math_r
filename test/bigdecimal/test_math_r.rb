# frozen_string_literal: true

require "test_helper"

class TestBigMathR < Minitest::Test

  PREC = 20

  def test_bigmathr

    BigMathR.LOG2(PREC)

    assert BigMathR.log(0, PREC) == -BigDecimal::INFINITY
    assert BigMathR.log(2, PREC).to_f == BigMath.log(2, PREC).to_f


    assert BigMathR.atan(3, 4, PREC) == BigMathR.atan2(4, 3, PREC)

    assert BigMathR.sqrt(-1, PREC) == Complex::I


    assert BigMathR.hypot(3, 4, PREC) == 5

  end

end
