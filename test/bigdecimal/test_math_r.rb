# frozen_string_literal: true

require "test_helper"

class TestMathR < Minitest::Test

  def test_logarithm

    #=> Big in Ver.Beta, there's an error 5.859375e-46
    assert (BigMathR::EDF.log(700, 100) - BigMath.log(700, 100)).to_f == -0.7e-99

  end

end
