import sys

def sieve(n):
	primes = []
	isPrime = [True] * (n+1)
	for i in range(2, n+1):
		if isPrime[i]:
			primes.append(i)
		for p in primes:
			d = i * p
			if d > n:
				break
			isPrime[d] = False
			if i % p == 0:
				break
	return primes

primes = sieve(1000)
prod = 1
i = 0
ans = []
while prod <= 10**43:
	ans.append(prod)
	prod = prod * primes[i]
	i += 1

tests = [int(x.rstrip('\n')) for x in sys.stdin.readlines()]
for n in tests:
	j = 0
	while True:
		if ans[j] > n:
			break
		j += 1
	print(ans[j-1])