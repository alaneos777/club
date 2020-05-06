def inverse(a, b):
	r0 = a
	r1 = b
	s0 = 1
	s1 = 0
	t0 = 0
	t1 = 1
	while r1 != 0:
		q = r0 // r1
		ri = r0 - r1 * q
		r0 = r1
		r1 = ri
		si = s0 - s1 * q
		s0 = s1
		s1 = si
		ti = t0 - t1 * q
		t0 = t1
		t1 = ti
	return (s0, t0)

digits = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd']
def base14(n):
	cad = ""
	while n > 0:
		d = digits[n % 14]
		cad = d + cad
		n //= 14
	return cad

def count(n):
	lst = []
	while n > 0:
		d = n % 14
		n //= 14
		lst = [d] + lst
	r = 1
	ans = 0
	for d in lst:
		ans += d * r
		if d > 0:
			r += 1
	return ans

n = 10000
two = 2**n
seven = 7**n
fourteen = 14**n
(s, t) = inverse(seven, two)
x1 = seven * s % fourteen
x2 = two * t % fourteen

suma = 1 + count(x1) + count(x2)

print(base14(suma))