# frozen_string_literal: true

require 'bigdecimal/util'

def bernoulli_list(_N)
  raise ArgumentError, "argument N must be Integer" unless _N.class == Integer
  raise RangeError, "negative number" if _N.negative?

  b_n = Hash.new
  b_n[0] = 1/1r
  b_n[1] = -1/2r

  t = []
  (_N+1).times { t.push(0) }
  q = 1
  t[1] = 1
  for n in 2.._N
    for i in 1...n; t[i - 1] = i * t[i]; end
    t[n - 1] = 0
    n.downto(2) {|i| t[i] += t[i - 2] }
    if (n % 2 == 0) 
      q *= 4
      b1 = n * t[0];  b2 = q * (q - 1)
      r = n % 4 == 0 ? Rational(-b1, b2) : Rational(b1, b2)
      b_n[n] = r
    end
  end
  b_n
end

def factorial_list(_N)
  raise ArgumentError, "argument N must be Integer" unless _N.class == Integer
  raise RangeError, "negative number" if _N.negative?

  f_n = Hash.new
  f_n[0] = 1

  (1.._N).inject(1) { |product, i| f_n[i] = product * i }

  f_n
end

def hoen_list(_N)
  raise ArgumentError, "argument N must be Integer" unless _N.class == Integer
  raise RangeError, "negative number" if _N.negative?

  b_n = bernoulli_list(_N)
  f_n = factorial_list(_N)
  h_n = Hash.new

  for n in 2.._N
    if b_n.key?(n)
      h_n[n] = b_n[n]/f_n[n]
    end
  end

  h_n
end

def show_bernoulli_list(_N)
  bernoulli_list(_N).each do |k, v|
    puts "|B(%#{_N.digits.size}d)| = %s" % [k, v]
  end
end

def show_factorial_list(_N)
  factorial_list(_N).each do |k, v|
    puts "|%#{_N.digits.size}d!| = %s" % [k, v]
  end
end

def show_hoen_list(_N)
  hoen_list(_N).each do |k, v|
    puts "|B%#{_N.digits.size}d/%#{_N.digits.size}d!| = %s" % [k, k, v]
  end
end


def main
  show_hoen_list(80)
end

main
