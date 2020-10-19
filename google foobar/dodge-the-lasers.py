from decimal import *

def gcd(a, b):
	while b != 0:
		(a, b) = (b, a % b)
	return a

def f(a, b, c, n, r):
	getcontext().prec = 200
	w = Decimal(r).sqrt()
	if n == 0:
		return 0
	if n == 1:
		return int((a*w + b) / c)
	gg = gcd(a, gcd(b, c))
	a //= gg
	b //= gg
	c //= gg
	res = int((a*w + b) / c)
	if res == 0:
		gg = gcd(a*c, gcd(b*c, a*a*r - b*b))
		nn = int((a*w + b) / c * n)
		return nn*n - f(a*c/gg, -b*c/gg, (a*a*r - b*b)/gg, nn, r)
	else:
		return n*(n + 1) // 2 * res + f(a, b - res*c, c, n, r)

def solution(s):
	return str(f(1, 0, 1, int(s), 2))