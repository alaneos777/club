from decimal import *
getcontext().prec = 100

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
		num = x * eval(t, x) - eval(s, x)
		den = x * evald(t, x) + eval(t, x) - evald(s, x)
		#print(F"#{i} {num}/{den} {num/den}")
		x -= num / den
	return x

s = [Decimal('1')]
t = []
minimum = Decimal('0.5')
maximum = Decimal('0.5')

i = 2
ans = 0

while True:
	for r in s:
		t.append(r)

	S = []
	for r in s:
		S.append((r+2 - (r*r + 4*r).sqrt()) / 2)
		S.append((r+2 + (r*r + 4*r).sqrt()) / 2)
	s = S
	s.sort()
	t.sort()

	# for r in s:
	# 	print(F"{r} ", end='')
	# print("")
	# print("")
	# for r in t:
	# 	print(F"{r} ", end='')
	# print("")
	# print("")
	# print("")

	minimum = solve(s, t, minimum**2)
	maximum = solve(s, t, maximum+2)
	if maximum > 25:
		break
	print(F"!{minimum.sqrt()} {maximum.sqrt()} {minimum * eval(t, minimum) - eval(s, minimum)} {maximum * eval(t, maximum) - eval(s, maximum)}")
	ans += (minimum.sqrt() + maximum.sqrt()) * (2**i-2)
	print(ans)
	print("")


	i += 1