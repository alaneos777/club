import sys

M = 66
prods = [[1 for j in range(M+1)] for i in range(M+1)]
for l in range(1, M+1):
	prods[l][l] = l
	for r in range(l+1, M+1):
		prods[l][r] = prods[l][r-1] * r

def mult(a, b):
	n = len(a)
	c = [0] * n
	for i in range(n):
		for j in range(n):
			if i+j >= n: break
			c[i+j] += a[i]*b[j]
	return c

def F(length, cnt, c, n):
	poly = [0] * (cnt+1)
	poly[0] = 1
	for i in range(n):
		curr = [0] * (cnt+1)
		for j in range((c[i]+length-1)//length, cnt+1):
			curr[j] = prods[j+1][cnt]
		poly = mult(poly, curr)
	return poly[cnt] // prods[1][cnt] ** (n-1)

data = [linea.rstrip("\n") for linea in sys.stdin.readlines()]
for caso in range(1, len(data), 2):
	n, p = map(int, data[caso].split())
	c = list(map(int, data[caso+1].split()))
	ans = (F(1, 60, c, n) + 24*F(5, 12, c, n) + 20*F(3, 20, c, n) + 15*F(2, 30, c, n)) // 60
	print(F"{ans % p}")