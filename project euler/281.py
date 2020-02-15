M = 1000

fact = [1, 1]
for i in range(2, M+1):
	fact.append(fact[i-1] * i)

phi = list(range(0, M+1))
for i in range(2, M+1):
	if phi[i] == i:
		for j in range(i, M+1, i):
			phi[j] -= phi[j] // i

divisors = [[] for i in range(M+1)]
for i in range(1, M+1):
	for j in range(i, M+1, i):
		divisors[j].append(i)

def f(m, n):
	ans = 0
	for d in divisors[n]:
		ans += fact[m*d] // fact[d]**m * phi[n//d]
	ans //= m*n
	return ans

acum = 0
limit = 10**15
m = 2
while True:
	n = 1
	if f(m, 1) > limit:
		break
	while True:
		c = f(m, n)
		if c > limit:
			break
		acum += c
		print(F"f({m}, {n}) = {c}")
		n += 1
	m += 1

print(acum)
