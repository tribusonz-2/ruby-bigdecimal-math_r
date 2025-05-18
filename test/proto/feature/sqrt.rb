require 'benchmark'
require 'bigdecimal'
require './math_r'

# Reference: C-gengo ni yoru hyoujun algorithm jiten
def sqrt_newton(x, prec)
  raise ArgumentError, "Zero or negative precision" if prec <= 0
  s = 0; last = 0
  n = BigDecimal.double_fig + prec
  if x.zero?
    return BigDecimal('0')
  elsif x.positive?
    return x if x.infinite?
    s = (x > 1) ? x : BigDecimal('1')
    loop do
      last = s;
      s = (x / s + s).div(2, n)
      break if !(s < last)
    end
    return last.round(prec)
  else 
  end
  return BigDecimal::NAN
end


def benchmark(x, prec, _N)
  puts "x = #{x}, precision = #{prec}, N = #{_N}"
  Benchmark.bm(16) do |bmx|
    bmx.report("BigDecimal#sqrt") { for i in 1.._N do; x.sqrt(prec) end }
    bmx.report("mysqrt (Ruby)") { for i in 1.._N do; sqrt_newton(x, prec) end }
    bmx.report("mysqrt (C)") { for i in 1.._N do; BigMathR::PowerRoot.sqrt(x, prec) end }
  end
  puts
end

def main
  x = BigDecimal('2')

  benchmark(x, 2252, 1)
  benchmark(x, 2253, 1)

end

main
#=> x = 0.2e1, precision = 2252, N = 1
#=>                        user     system      total        real
#=> BigDecimal#sqrt    0.001192   0.000057   0.001249 (  0.001248)
#=> mysqrt (Ruby)      0.005200   0.000046   0.005246 (  0.005246)
#=> 
#=> x = 0.2e1, precision = 2253, N = 1
#=>                        user     system      total        real
#=> BigDecimal#sqrt    1.066908   0.000000   1.066908 (  1.067088)
#=> mysqrt (Ruby)      0.005285   0.000000   0.005285 (  0.005285)
