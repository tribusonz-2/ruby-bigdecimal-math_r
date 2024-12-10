require 'bigdecimal/math'
require 'bigdecimal/util' 

module BigMath
  module_function

  def log2(x, prec)
    raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
    raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0

    x = x.to_d(prec) unless x.class == BigDecimal

    return -BigDecimal::INFINITY if x.zero?
    if x.positive?
      return BigDecimal::INFINITY if x.infinite?
      y = log(x, prec) / log(2, prec)
      return y.round(prec)
    end
    BigDecimal::NAN
  end

  def log10(x, prec)
    raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
    raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0

    x = x.to_d(prec) unless x.class == BigDecimal

    return -BigDecimal::INFINITY if x.zero?
    if x.positive?
      return BigDecimal::INFINITY if x.infinite?
      y = log(x, prec) / log(10, prec)
      return y.round(prec)
    end
    BigDecimal::NAN
  end

  def cbrt(x, prec)
    raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
    raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0

    x = x.to_d(prec) unless x.class == BigDecimal

    return x if x.nan? || x.infinite?
    sign = x.negative? ? -1 : 1
    y = sign * BigDecimal((sign * x).to_s, prec) ** Rational(1, 3).to_d(prec)
    y.round(prec)
  end

  def exp2(x, prec)
    raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
    raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0

    x = x.to_d(prec) unless x.class == BigDecimal

    return x if x.nan?
    x *= log(BigDecimal('2'), prec) 
    y = exp(x, prec)
    y.round(prec)
  end

  def tan(x, prec)
    raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
    raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0

    x = x.to_d(prec) unless x.class == BigDecimal

    return x if x.nan? || x.infinite?
    y = sin(x, prec) / cos(x, prec)
    y.round(prec)
  end

  def asin(x, prec)
    raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
    raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0

    x = x.to_d(prec) unless x.class == BigDecimal

    return x if x.nan?
    if (x >= -1 && x <= 1)
      y = atan((x / sqrt(1 - x * x, prec)), prec)
      return y.round(prec)
    end
    BigDecimal::NAN
  end

  def acos(x, prec)
    raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
    raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0

    x = x.to_d(prec) unless x.class == BigDecimal

    return x if x.nan?
    if (x >= -1 && x <= 1)
      y = 0
      if x == 1
        y = BigDecimal('0', prec)
      elsif x == -1
        y = PI(prec)
      else
        y = PI(prec) / 2 - asin(x, prec)
      end
      return y.round(prec)
    end
    BigDecimal::NAN
  end

  def sinh(x, prec)
    raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
    raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0

    x = x.to_d(prec) unless x.class == BigDecimal

    return x if (x.nan? || x.infinite?)
    exppx = exp( x, prec)
    expmx = exp(-x, prec)
    y = exppx / 2 - expmx / 2
    y.round(prec)
  end

  def cosh(x, prec)
    raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
    raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0

    x = x.to_d(prec) unless x.class == BigDecimal

    return x if x.nan?
    return BigDecimal::INFINITY if x.infinite?
    exppx = exp( x, prec)
    expmx = exp(-x, prec)
    y = expmx / 2 + exppx / 2
    y.round(prec)
  end

  def tanh(x, prec)
    raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
    raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0

    x = x.to_d(prec) unless x.class == BigDecimal

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
    raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
    raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0

    x = x.to_d(prec) unless x.class == BigDecimal

    return x if (x.nan? || x.infinite?)
    y = log(sqrt(x * x + 1, prec) + x, prec)
    y.round(prec)
  end

  def acosh(x, prec)
    raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
    raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0

    x = x.to_d(prec) unless x.class == BigDecimal

    return x if x.nan?
    if x >= 1
      y = log(x + sqrt(x - 1, prec) * sqrt(x + 1, prec), prec)
      return y.round(prec)
    end
    BigDecimal::NAN
  end

  def atanh(x, prec)
    raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
    raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0

    x = x.to_d(prec) unless x.class == BigDecimal

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
    raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
    raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0

    x = x.to_d(prec) unless x.class == BigDecimal

    return BigDecimal::NAN if x.nan? || y.nan?
    return BigDecimal::INFINITE if x.infinite? || y.infinite?
    sqrt(x * x + y * y, prec).round(prec)
  end

  def lgamma(x, prec)
    raise ArgumentError, "precision must be an Integer" unless prec.class == Integer
    raise ArgumentError, "Zero or negative precision for #{__method__}" if prec <= 0

    x = x.to_d(prec) unless x.class == BigDecimal

    return BigDecimal('0', prec) if x == 1 or x == 2

    # Positive Argument Routine  (Reference: Haruhiko Okumura: C-gengo ni yoru hyoujun algorithm jiten)
    positive = lambda do
      log_2pi = log(PI(prec) * 2, prec)  # $\log 2\pi$ 
      n = 8
      coef = [
           1/12r,     # B_2  / ( 2 *  1) =     1/12
          -1/360r,    # B_4  / ( 4 *  3) =    -1/360
           1/1260r,   # B_6  / ( 6 *  5) =     1/1260
          -1/1680r,   # B_8  / ( 8 *  7) =    -1/1680
           1/1188r,   # B_10 / (10 *  9) =     1/1188
        -691/360360r, # B_12 / (12 * 11) =  -691/360360
           1/156r,    # B_14 / (14 * 13) =     1/156
       -3617/122400r  # B_16 / (16 * 15) = -3617/122400
      ]
      v = 1
      while (x < n);  v *= x;  x += 1;  end
      w = 1 / (x * x)

      y =  (((((((coef[7]  * w + coef[6]) * w + coef[5]) * w + coef[4]) * w\
                + coef[3]) * w + coef[2]) * w + coef[1]) * w + coef[0]) / x\
                + 0.5 * log_2pi - log(v, prec) - x + (x - 0.5) * log(x, prec)
      y.round(prec)
    end
    
    # Negative Argument Routine
    negative = lambda do
      s = (1 / sin(PI(prec) * x, prec).round(prec)).abs

      return BigDecimal::INFINITY if s.infinite? or s.exponent > prec

      x = 1 - x
      y = log(s, prec) - positive.call + log(PI(prec), prec)
      y.round(prec)
    end

    case x
    when BigDecimal::NAN
      BigDecimal::NAN
    when BigDecimal::INFINITY
      x.negative? ? BigDecimal::NAN : BigDecimal::INFINITY
    when BigDecimal('0')
      BigDecimal::INFINITY
    else # BigDecimal # Finite
      x.negative? ? negative.call : positive.call
    end
  end

end

