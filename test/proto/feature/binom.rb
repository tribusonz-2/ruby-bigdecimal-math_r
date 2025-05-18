

def binom(n, k)
  return 1 if n == k
  t1, t1_sign = Math.lgamma(n+1)
  t2, t2_sign = Math.lgamma(k+1)
  t3, t3_sign = Math.lgamma(-k+n+1)
  sign = (t1_sign / (t2_sign * t3_sign))
  y = sign * Math.exp(t1 - (t2 + t3))
  y = y.round if [n, k].all?(&:integer?)
  y
end

