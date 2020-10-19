mod = 10**8 + 7

def rec(P, init, n):
	deg = len(P)
	ans = [0] * deg
	ans[0] = 1
	R = [0] * (2 * deg)
	p = 1
	v = n
	v >>= 1
	while v > 0:
		p <<= 1
		v >>= 1
	while True:
		d = 1 if (n & p) != 0 else 0
		for i in range(len(R)):
			R[i] = 0
		for i in range(deg):
			for j in range(deg):
				R[i + j + d] = (R[i + j + d] + ans[i] * ans[j]) % mod
		for i in range(deg-1, -1, -1):
			for j in range(deg):
				R[i + j] = (R[i + j] + R[i + deg] * P[j]) % mod
		for i in range(deg):
			ans[i] = R[i]
		p >>= 1
		if p == 0:
			break
	val = 0
	for i in range(deg):
		val = (val + ans[i] * init[i]) % mod
	return val

initial = [1, 229, 117805, 64647289, 35669566217, 19690797527709, 
10870506600976757, 6001202979497804657, 3313042830624031354513, 
1829008840116358153050197, 1009728374600381843221483965, 
557433823481589253332775648233, 307738670509229621147710358375321, 
169891178715542584369273129260748045, 
93790658670253542024618689133882565125, 
51778366130057389441239986148841747669217, 
28584927722109981792301610403923348017948449, 
15780685138381102545287108197623881881376915397, 
8711934690116480171969789787256390490181022415693]

poly = [1, -675, 73471, -3221189, 72583272, -925908264, 6971103216,
-31523058272, 86171526770, -142604534086, 142604534086, -86171526770,
31523058272, -6971103216, 925908264, -72583272, 3221189, -73471, 675]

print(rec(poly, initial, 10**10000//2))