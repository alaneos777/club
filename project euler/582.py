import math
from decimal import *

getcontext().prec = 100

def FloorSqrt(n):
	r = Decimal(n).sqrt()
	return int(r)

init = []
n = 1
while True:
	lo = n + 1
	hi = n + FloorSqrt(3*n**2 + 100)
	if n >= 6:
		lo = n + FloorSqrt(3*n**2 - 100) + 1
	if hi >= lo:
		init.append(n)
		if len(init) == 500:
			break
	n += 1

L = 10**100

while init[-1]**2 <= L:
	init.append(4*init[-78] - init[-156])
while init[-1] > L:
	init.pop()

ans = 0

for n in init:
	lo = n + 1
	hi = n + FloorSqrt(3*n**2 + 100)
	if n >= 6:
		lo = n + FloorSqrt(3*n**2 - 100) + 1
	for m in range(lo, hi+1):
		if math.gcd(m, n) == 1 and (m - n) % 3 != 0:
			a = m**2 - n**2
			b = 2*m*n + n**2
			c = m**2 + m*n + n**2
			ans += min(L//c, 100//abs(a-b))

print(ans)
