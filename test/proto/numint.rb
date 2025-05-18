#/***********************************************************
#    numint.rb -- 数値積分
#***********************************************************/


def integrade_fin(a, b, nmax, &integrand)
  hash = { :trapezoid => 0.0, :midpoint => 0.0, :simpson => 0.0 }
  h = b - a;  hash[:trapezoid] = h * (integrand.call(a) + integrand.call(b)) / 2.0
  printf("    n 台形             中点             Simpson\n")
  n = 1; while (n <= nmax)
    hash[:midpoint] = 0
    for i in 1..n; hash[:midpoint] += integrand.call(a + h * (i - 0.5)); end
    hash[:midpoint] *= h
    hash[:simpson] = (hash[:trapezoid] + 2 * hash[:midpoint]) / 3.0
    printf("%5d % -16.16s % -16.16s % -16.16s\n",\
        n, hash[:trapezoid], hash[:midpoint], hash[:simpson])
    h /= 2.0;  hash[:trapezoid] = (hash[:trapezoid] + hash[:midpoint]) / 2.0
    n *= 2
  end
  [hash[:trapezoid], hash[:midpoint], hash[:simpson]]
end

def test1
  integrade_fin(0, 1, 32) {|t| 4 / (1 + t * t) }
end

def test2
  integrade_fin(0, 1, 1024) {|t| 1.0/Math.log(t) + 1.0/(1 - t) }
end

def test3
  x = -4.5
  puts "erf(#{x})"
  trapezoid, midpoint, simpson = integrade_fin(0, x, 512) {|t| Math.exp(-t * t) }
  c = 2 / Math.sqrt(Math::PI)
  puts "%5s % -16.16s % -16.16s % -16.16s\n" % [" ", trapezoid * c, midpoint * c, simpson * c]
  puts "gcc erf(#{x}) = #{Math.erf(x)}"
end

def test4(x)
  integrade_fin(0, x, 1024) {|t| Math.sin((Math::PI * t * t) / 2) }
end

test1
test2
test3
test4(1.5r)


def integrade_inf(_N=50000, &integrand)
  dx = Rational(1, _N)
  _S = 0.0;
  for i in 1.._N do
    _S += (integrand.call(i * dx) + integrand.call((i + 1) * dx)) / 2.0 * dx
  end
  _S
end

s = integrade_inf {|t| Math::PI * Math.exp(-(Math.tan(Math::PI*t/2)**2))/(2*(Math.cos(Math::PI*t/2)**2)) }
p 2*s 
