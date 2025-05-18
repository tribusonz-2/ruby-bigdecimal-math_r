# frozen_string_literal: true

require 'benchmark'
require 'bigdecimal/math'

PREC = 1000

PADDING = "\t"

def print_const(const_name, type: :ruby, &block)
  const = block.call


  raise TypeError, "not a BigDecimal" unless const.class == BigDecimal

  array = const.to_s.split(/[.|e]/)

  if array.size == 1
    File.write("const/"+const_name+".txt", const.to_s)
  else
    pre = array.shift.rjust(4, " ") + '.'
    raws = []
    text = String.new
    raw_array = array.shift.scan(/.{1,5}/)
    raw_array.each_with_index do |numb, i|
      case i % 5
      when 0
        raws << pre
        raws << numb
      when 4
        raws << numb
        text << raws.join(' ')
        text << "\n"
        raws.clear
        pre = " "*5
      else
        raws << numb
      end
      if i == (raw_array.size-1)
        unless raws.size == 0
          text << raws.join(' ')
          text << "\n"
          raws.clear
        end
      end
    end
    if !array.empty?
      pre = " "*5
      raws << pre
      raws << "e#{array.shift}"
      text << raws.join(' ')
    end
    File.write("const/"+const_name+".txt", text)
  end
  
end


CALC = [
  [ 'PI',          lambda { BigMath.PI(PREC).round(PREC) } ],
  [ '2PI',         lambda { (2 * BigMath.PI(PREC)).round(PREC) } ],
  [ 'LOGPI',       lambda { BigMath.log(BigMath.PI(PREC), PREC).round(PREC) } ],
  [ 'TWO_SQRTPI',  lambda { (2 / BigMath.sqrt(BigMath.PI(PREC), PREC)).round(PREC) } ],
  [ 'SQRT_TWO_PI', lambda { BigMath.sqrt(2 / BigMath.PI(PREC), PREC).round(PREC) } ],
  [ 'SQRT2',       lambda { BigMath.sqrt(BigDecimal(2), PREC).round(PREC) } ],
  [ 'E',           lambda { BigMath.E(PREC).round(PREC) } ],
  [ 'LOG2',        lambda { BigMath.log(2, PREC).round(PREC) } ]
]


def bench
  puts "Precision = #{PREC}"

  Benchmark.bm(20) do |x|
    CALC.each do |name, lamb|
      x.report(name) { lamb }
    end
  end
end

def print_text
  CALC.each do |name, lamb|
    print_const(name) {lamb.call}
  end
end


def main

# bench

  print_text

end

main
