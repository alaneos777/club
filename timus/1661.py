import sys

M = 30
fact = [1] * (M+1)
for i in range(2, M+1):
	fact[i] = i * fact[i-1]

def multi(d, j):
	ans = fact[d]
	for ji in j:
		ans //= fact[ji]
	return ans


def extract(l, d, expo):
	j = []
	for e in expo:
		if e % l == 0:
			j.append(e // l)
	if len(j) != len(expo):
		return 0
	else:
		return multi(d, j)

data = [linea.rstrip("\n") for linea in sys.stdin.readlines()]
freq = {}
for linea in data:
	for c in map(int, linea.split()):
		if not c in freq:
			freq[c] = 0
		freq[c] += 1

expo = [v for k, v in freq.items()]
ans = 0

for l, d, coef in zip([1, 5, 3], [30, 6, 10], [1, 24, 20]):
	ans += coef * extract(l, d, expo)

for i in range(len(expo)):
	expo[i] -= 2
	if expo[i] >= 0:
		ans += 15*extract(2, 14, expo)
	expo[i] += 2

for i in range(len(expo) - 1):
	expo[i] -= 1
	for j in range(i+1, len(expo)):
		expo[j] -= 1
		ans += 30*extract(2, 14, expo)
		expo[j] += 1
	expo[i] += 1

ans //= 60
print(ans)