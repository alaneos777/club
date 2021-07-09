def euler718(k):
  d1,d2,d3 = 17**k,19**k,23**k
  # https://en.wikipedia.org/wiki/Numerical_semigroup#R%C3%B6dseth's_algorithm
  s, s_prev = modinv(d2,d1) * d3 % d1, d1
  p, p_prev = 1, 0
  r = (s*d2-p*d3)//d1
  while r > 0:
    q = (s_prev-1)//s+1
    s, s_prev = q*s-s_prev,s
    p, p_prev = q*p-p_prev, p
    r, r_prev = (s*d2-p*d3)//d1, r
  a1,a2,a3 = r_prev-r, s_prev, p
  # Formula 24  & 25 from "Power Sums Related to Semigroups S(d1, d2, d3)" 
  #   by Fel & Rubinstein
  ad1,ad2,ad3 = a1*d1, a2*d2, a3*d3
  pi_d = d1*d2*d3
  pi_a = a1*a2*a3
  s_d = d1+d2+d3
  s_ad = ad1+ad2+ad3
  g0 = (1 - s_d - pi_a + s_ad)//2
  g1 = s_ad*(s_ad-3*s_d-2*pi_a) + s_d*(s_d+3*pi_a) + (d1*d2 + d1*d3 + d2*d3) + pi_d - 1
  g1 += ad1*ad1 + ad2*ad2 + ad3*ad3
  g1 //= 12 
  return g1 + s_d*(s_d-1)//2 + g0*s_d
  
def modinv(b, n):
  x0, x1 = 1, 0
  while n:
    (q, n), b = divmod(b,n), n
    x0, x1 = x1, x0 - q * x1
  return x0

print(euler718(7))