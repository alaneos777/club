from decimal import *
getcontext().prec = 1000

def eval(roots, x):
	ans = Decimal('1')
	for r in roots:
		ans *= x - r
	return ans

def evald(roots, x):
	prod = eval(roots, x)
	ans = Decimal('0')
	for r in roots:
		ans += prod / (x - r)
	return ans

def solve(s, t, x = 0.5):
	for i in range(200):
		num = x*x * eval(t, x) - eval(s, x)
		den = x*x * evald(t, x) + 2*x * eval(t, x) - evald(s, x)
		#print(F"#{i} {num}/{den} {num/den}")
		x -= num / den
	return x

s = [Decimal('0')]
t = []
minimum = Decimal('0.707')
maximum = Decimal('0.707')
i = 1

while True:
	S = []
	for r in s:
		S.append((r - (r*r + 4).sqrt()) / 2)
		S.append((r + (r*r + 4).sqrt()) / 2)
	s = S
	s.sort()
	t.sort()

	if i > 1:
		# for r in s:
		# 	print(F"{r} ", end='')
		# print("")
		# for r in t:
		# 	print(F"{r} ", end='')
		# print("")
		minimum = solve(s, t, minimum * Decimal('0.1'))
		maximum = solve(s, t, maximum * Decimal('2'))
		if maximum > 25:
			break
		print(F"!{minimum} {maximum} {minimum**2 * eval(t, minimum) - eval(s, minimum)} {maximum**2 * eval(t, maximum) - eval(s, maximum)}")
		print("")

	for r in s:
		t.append(r)

	i += 1