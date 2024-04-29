require 'bigdecimal/math'
require 'bigdecimal/util' 

module BigMath
  module_function

  def log2(x, prec)
    return -BigDecimal::INFINITY if x.zero?
    if x.positive?
      return BigDecimal::INFINITY if x.infinite?
      y = log(x, prec) / log(2, prec)
      return y.round(prec)
    end
    BigDecimal::NAN
  end

  def log10(x, prec)
    return -BigDecimal::INFINITY if x.zero?
    if x.positive?
      return BigDecimal::INFINITY if x.infinite?
      y = log(x, prec) / log(10, prec)
      return y.round(prec)
    end
    BigDecimal::NAN
  end

  def cbrt(x, prec)
    return x if x.nan? || x.infinite?
    sign = x.negative? ? -1 : 1
    y = sign * BigDecimal((sign * x).to_s, prec) ** Rational(1, 3).to_d(prec)
    y.round(prec)
  end

  def exp2(x, prec)
    return x if x.nan?
    x *= BigMath.log(BigDecimal('2'), prec) 
    y = exp(x, prec)
    y.round(prec)
  end

  def tan(x, prec)
    return x if x.nan? || x.infinite?
    y = sin(x, prec) / cos(x, prec)
    return y.round(prec)
  end

  def asin(x, prec)
    return x if x.nan?
    if (x >= -1 && x <= 1)
      y = atan((x / sqrt(1 - x * x, prec)), prec)
      return y.round(prec)
    end
    BigDecimal::NAN
  end

  def acos(x, prec)
    return x if x.nan?
    if (x >= -1 && x <= 1)
      y = BigMath::PI(prec) / 2 - asin(x, prec)
      return y.round(prec)
    end
    BigDecimal::NAN
  end

  def sinh(x, prec)
    return x if (x.nan? || x.infinite?)
    exppx = exp( x, prec)
    expmx = exp(-x, prec)
    y = exppx / 2 - expmx / 2
    y.round(prec)
  end

  def cosh(x, prec)
    return x if x.nan?
    return BigDecimal::INFINITY if x.infinite?
    exppx = exp( x, prec)
    expmx = exp(-x, prec)
    y = expmx / 2 + exppx / 2
    y.round(prec)
  end

  def tanh(x, prec)
    return x if x.nan?
    if x.infinite?
      return x < 0 ? BigDecimal('-1') : BigDecimal('1')
    end
    exppx = exp( x, prec)
    expmx = exp(-x, prec)
    y = exppx / (expmx + exppx) - expmx / (expmx + exppx)
    y.round(prec)
  end

  def asinh(x, prec)
    return x if (x.nan? || x.infinite?)
    y = log(sqrt(x * x + 1, prec) + x, prec)
    y.round(prec)
  end

  def acosh(x, prec)
    return x if x.nan?
    if x >= 1
      y = log(x + sqrt(x - 1, prec) * sqrt(x + 1, prec), prec)
      return y.round(prec)
    end
    BigDecimal::NAN
  end

  def atanh(x, prec)
    if x >= -1 && x <= 1
      half = Rational(1, 2).to_d(prec)
      logp1 = (x + 1) == 0 ? -BigDecimal::INFINITY : log(x + 1, prec)
      logm1 = (1 - x) == 0 ? -BigDecimal::INFINITY : log(1 - x, prec)
      y = half * logp1 - half * logm1
      return y.round(prec)
    end
    BigDecimal::NAN
  end

  def hypot(x, y, prec)
    return BigDecimal::NAN if x.nan? || y.nan?
    return BigDecimal::INFINITE if x.infinite? || y.infinite?
    sqrt(x * x + y * y, prec).round(prec)
  end
end

