from itertools import cycle, product

def gcd(a, b):
	while b != 0:
		(a, b) = (b, a % b)
	return a

class Pt:
	def __init__(self, x=0, y=0):
		self.x = x
		self.y = y
	def __add__(self, p):
		return Pt(self.x + p.x, self.y + p.y)
	def __sub__(self, p):
		return Pt(self.x - p.x, self.y - p.y)
	def __str__(self):
		return "({0},{1})".format(self.x, self.y)
	def norm(self):
		return self.x**2 + self.y**2
	def unit(self):
		d = gcd(abs(self.x), abs(self.y))
		if d == 0:
			d = 1
		return Pt(self.x // d, self.y // d)
	def __hash__(self):
		return hash((self.x, self.y))
	def __eq__(self, p):
		return self.x == p.x and self.y == p.y

def gen_d(start, lim, dirs):
	for d in cycle(dirs):
		start = start + d
		if start.norm() > lim*lim:
			break
		yield start

def gen(origin, pos, dims, lim):
	(w, h) = dims
	(l, r) = (pos.x, w - pos.x)
	(d, u) = (pos.y, h - pos.y)
	disps_x = [Pt(0, 0)]
	disps_y = [Pt(0, 0)]
	for dir in gen_d(pos - origin, lim, [Pt(2*r, 0), Pt(2*l, 0)]):
		disps_x.append(dir - pos + origin)
	for dir in gen_d(pos - origin, lim, [Pt(-2*l, 0), Pt(-2*r, 0)]):
		disps_x.append(dir - pos + origin)
	for dir in gen_d(pos - origin, lim, [Pt(0, 2*u), Pt(0, 2*d)]):
		disps_y.append(dir - pos + origin)
	for dir in gen_d(pos - origin, lim, [Pt(0, -2*d), Pt(0, -2*u)]):
		disps_y.append(dir - pos + origin)
	for dx, dy in product(disps_x, disps_y):
		if (pos - origin + dx + dy).norm() <= lim*lim:
			yield pos + dx + dy

def solution(dimensions, your_position, guard_position, distance):
	your_position = Pt(your_position[0], your_position[1])
	guard_position = Pt(guard_position[0], guard_position[1])
	forbidden = gen(your_position, your_position, dimensions, distance)
	targets = gen(your_position, guard_position, dimensions, distance)
	vecs = dict()
	for target in targets:
		vec = (target - your_position).unit()
		if not vec in vecs:
			vecs[vec] = set()
		vecs[vec].add((target, 1))
	for me in forbidden:
		vec = (me - your_position).unit()
		if not vec in vecs:
			vecs[vec] = set()
		vecs[vec].add((me, 0))
	ans = 0
	for vec, points in vecs.iteritems():
		hasGuard = False
		mini = 0
		who = -1
		for pt in points:
			hasGuard = hasGuard or (pt[1] == 1)
			if who == -1 or (pt[0] - your_position).norm() < mini:
				who = pt[1]
				mini = (pt[0] - your_position).norm()
		if hasGuard and who == 1:
			ans += 1
	return ans