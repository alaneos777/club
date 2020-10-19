import sys

sys.setrecursionlimit(10**5)

flag = False

def shuffle(lst):
	return sorted(lst, reverse=flag)

def concat(lst1, lst2):
	return lst1 + lst2

[a, b] = [x.rstrip('\n') for x in sys.stdin.readlines()]
x = eval(a)
y = eval(b)
flag = True
z = eval(a)
w = eval(b)

if x == y and z == w:
	print("equal")
else:
	print("not equal")