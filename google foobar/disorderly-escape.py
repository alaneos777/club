import sys

def gen_frequencies(n, rem, pos = 1):
	if pos == n:
		if rem % pos == 0:
			yield (rem // pos,)
	else:
		i = 0
		while i*pos <= rem:
			for tmp in gen_frequencies(n, rem - i*pos, pos + 1):
				yield (i,) + tmp
			i += 1

fact = [1]
for i in range(1, 13):
	fact.append(i * fact[i-1])

def gen_all(n):
	ans = {}
	for freqs in gen_frequencies(n, n):
		den = 1
		freqs = (0,) + freqs
		for length in range(1, n+1):
			den *= (length ** freqs[length]) * fact[freqs[length]]
		ans[freqs] = fact[n] // den
	return ans

def gcd(a, b):
	while b != 0:
		(a, b) = (b, a % b)
	return a

def comb(n, m):
	ans = {}
	for freqs_a, coef_a in gen_all(n).items():
		for freqs_b, coef_b in gen_all(m).items():
			freqs = [0] * (n*m + 1)
			for p in range(1, n+1):
				for x in range(1, m+1):
					q = freqs_a[p]
					y = freqs_b[x]
					g = gcd(p, x)
					freqs[p // g * x] += q * y * g
			freqs = tuple(freqs)
			if not freqs in ans:
				ans[freqs] = 0
			ans[freqs] += coef_a * coef_b
	return ans

def solve(n, m, k):
	ans = 0
	for freqs, coef in comb(n, m).items():
		ans += coef * (k ** sum(freqs))
	ans //= fact[n] * fact[m]
	return str(ans)

(n, m, k) = map(int, sys.stdin.readline().split())
print(solve(n, m, k))