import sys

def manacher_odd(s):
	n = len(s)
	odd = [0] * n
	i, l, r = 0, 0, -1
	while i < n:
		k = 1 if i > r else min(odd[l + r - i], r - i + 1)
		while 0 <= i - k and i + k < n and s[i - k] == s[i + k]:
			k += 1
		odd[i] = k
		k -= 1
		if i + k > r:
			l = i - k
			r = i + k
		i += 1
	return odd

def manacher_even(s):
	n = len(s)
	even = [0] * n
	i, l, r = 0, 0, -1
	while i < n:
		k = 0 if i > r else min(even[l + r - i + 1], r - i + 1)
		while 0 <= i - k - 1 and i + k < n and s[i - k - 1] == s[i + k]:
			k += 1
		even[i] = k
		k -= 1
		if i + k > r:
			l = i - k - 1
			r = i + k
		i += 1
	return even

x = 31
mod = 10**18 + 3
x_inv = pow(x, mod-2, mod)
M = 10**5 + 10
x_pow = [1] * (M+1)
x_pow_inv = [1] * (M+1)
phi = [i for i in range(M+1)]
for i in range(2, M+1):
	if phi[i] == i:
		for j in range(i, M+1, i):
			phi[j] -= phi[j] // i

for i in range(1, M+1):
	x_pow[i] = x_pow[i-1] * x % mod
	x_pow_inv[i] = x_pow_inv[i-1] * x_inv % mod

def get_hash(s):
	n = len(s)
	hsh = [0] * n
	for i in range(n):
		hsh[i] = (ord(s[i]) - 96) * x_pow[i] % mod
		if i > 0:
			hsh[i] = (hsh[i] + hsh[i-1]) % mod
	return hsh

def hash_substr(hsh, i, j):
	ans = hsh[j]
	if i > 0: ans -= hsh[i-1]
	if ans < 0: ans += mod
	return ans * x_pow_inv[i] % mod

data = sys.stdin.readlines()
s = data[0].rstrip("\n")
k = int(data[1].rstrip("\n"))
n = len(s)

hsh = get_hash(s)
odd = manacher_odd(s)
even = manacher_even(s)
st = set()

for i in range(n):
	if len(st) == n: break
	for r in range(odd[i]-1, -1, -1):
		curr = hash_substr(hsh, i-r, i+r)
		if curr in st: break
		st.add(curr)
		if len(st) == n: break

for i in range(n):
	if len(st) == n: break
	for r in range(even[i]-1, -1, -1):
		curr = hash_substr(hsh, i-r-1, i+r)
		if curr in st: break
		st.add(curr)
		if len(st) == n: break

c = len(st)
ans = 0
for d in range(1, k+1):
	if k % d > 0: continue
	ans += phi[k//d] * c**d
if k % 2 == 0:
	ans += k * c**(k//2) * (c + 1) // 2
else:
	ans += k * c**((k+1)//2)
ans //= 2*k

print(ans)
