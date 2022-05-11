def extgcd(a, b):
	if b == 0:
		return (a, 2**a-1, 0, 0)
	else:
		q = a//b
		r = a - b*q
		(d, x, y, steps) = extgcd(b, r)
		return (d, y, x - y * (2**a - 2**r) // (2**b - 1), steps+1)

def gcd(a, b):
	if b == 0:
		return a
	else:
		return gcd(b, a%b)

mod = 10**9 + 7

for a in range(1, 101):
	for b in range(1, a):
		if gcd(a, b) == 1:
			(d, x, y, steps) = extgcd(a, b)
			if steps%2 == 0:
				y += 2**a-1
			assert((2**b-1)*y % (2**a-1) == 1)
			assert(0 <= y and y < 2**a-1)
			if steps%2 == 1:
				ans = 2 * (y + ((2**b-1)*y - 1)//(2**a-1)) - 2
			else:
				y = 2**a-1-y
				ans = 2 * (y + ((2**b-1)*y + 1)//(2**a-1)) - 2
			print(F"({a}, {b}) -> {ans % mod}")
	print("")
