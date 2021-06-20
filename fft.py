import numpy as np
import cmath
import time, timeit

def fft_ct(a, inv = 1):
	a = a.copy()
	n = len(a)
	j = 0
	for i in range(1, n-1):
		k = n>>1
		j^=k
		while j < k:
			k>>=1
			j^=k
		if i < j: a[i], a[j] = a[j], a[i]
	sz = 2
	while sz <= n:
		w = [cmath.exp(-2j * cmath.pi * j * inv / sz) for j in range(sz//2)]
		for start in range(0, n, sz):
			for j in range(0, sz//2):
				u, v = a[start + j], w[j] * a[start + j + sz//2]
				a[start + j], a[start + j + sz//2] = u + v, u - v
		sz<<=1
	if inv == -1: a /= n
	return a

def fft_stockham(a, inv = 1):
	n = len(a)
	sz = 2
	while sz <= n:
		b = a.copy()
		w = [cmath.exp(-2j * cmath.pi * j * inv / sz) for j in range(sz//2)]
		blocks = n//sz
		for j in range(0, sz//2):
			for block in range(0, blocks):
				u, v = a[block + (2*j)*blocks], w[j] * a[block + (2*j+1)*blocks]
				b[block + j*blocks], b[block + j*blocks + n//2] = u + v, u - v
		sz<<=1
		a = b
	if inv == -1: a /= n
	return a

def fft_stockham_v(a, inv = 1):
	n = len(a)
	a = a.reshape((n, 1))
	sz = 2
	while sz <= n:
		blocks = n//sz
		w = np.exp(-2j * np.pi * inv / sz * np.arange(0, sz//2))
		even = a[:blocks]
		odd = a[blocks:] * w
		a = np.hstack([even + odd, even - odd])
		sz<<=1
	if inv == -1: a /= n
	return a

tam = 1<<20
a = np.array([1,2,3,4,5,6,7,8])
a = np.random.rand(tam) + 1j*np.random.rand(tam)
t0 = timeit.default_timer()

a_hat = np.fft.fft(a)
t1 = timeit.default_timer()

a_hat2 = fft_ct(a.tolist())
t2 = timeit.default_timer()

a_hat3 = fft_stockham(a)
t3 = timeit.default_timer()

a_hat4 = fft_stockham_v(a)
t4 = timeit.default_timer()

print(F"Numpy: {t1-t0}")
print(F"CT: {t2-t1}")
print(F"Stockham: {t3-t2}")
print(F"Stockham vectorized: {t4-t3}")

print(np.allclose(a_hat, a_hat2, rtol=0, atol=1e-9))
print(np.allclose(a_hat, a_hat3, rtol=0, atol=1e-9))
print(np.allclose(a_hat, a_hat4, rtol=0, atol=1e-9))
