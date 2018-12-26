#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

struct point{
	lli x, y;

	point(): x(0), y(0){}
	point(lli x, lli y): x(x), y(y){}

	void read(){cin >> x >> y;}

	point operator-(const point & p) const{
		return point(x - p.x, y - p.y);
	}

	bool operator<(const point & p) const{
		if(x == p.x) return y < p.y;
		return x < p.x;
	}

	bool operator>(const point & p) const{
		if(x == p.x) return y > p.y;
		return x > p.x;
	}

	lli dot(const point & p) const{
		return x * p.x + y * p.y;
	}

	lli cross(const point & p) const{
		return x * p.y - y * p.x;
	}

	lli norm() const{
		return x*x + y*y;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	point init;
	init.read();
	vector<point> points(n);
	for(int i = 0; i < n; ++i) points[i].read();
	set<point> m;
	for(int i = 0; i < n; ++i){
		point v = points[i] - init;
		lli d = __gcd(abs(v.x), abs(v.y));
		v.x /= d, v.y /= d;
		if(v.x < 0){
			v.x *= -1, v.y *= -1;
		}
		if(v.x == 0){
			v.y = abs(v.y);
		}
		m.insert(v);
	}
	cout << m.size() << "\n";
	return 0;
}