import math, sys
from decimal import *

getcontext().prec = 1000

def Sqrt(n, k):
	if k < 0: k = 0
	r = str(Decimal(n).sqrt()).split(".")
	if k == 0:
		return r[0]
	elif len(r) == 1:
		return r[0] + "." + ("0"*k)
	else:
		return r[0] + "." + r[1][:k]

data = [linea.rstrip("\n") for linea in sys.stdin.readlines()]
n, k = map(int, data[0].split())

print(F"{Sqrt(n, k)}")