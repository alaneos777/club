#include <bits/stdc++.h>
using namespace std;
using ld = long double;

struct point{
	ld x, y;
	point(): x(0), y(0) {}
	point(ld x, ld y): x(x), y(y) {}
	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(ld k) const{return point(x * k, y * k);}
	ld dot(const point & p) const{return x*p.x + y*p.y;}
	ld length() const{return sqrtl(x*x + y*y);}
	point unit() const{
		ld len = length();
		return point(x / len, y / len);
	}
};

istream& operator>>(istream & is, point & p){
	return is >> p.x >> p.y;
}

ostream& operator<<(ostream & os, const point & p){
	return os << p.x << " " << p.y;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	point a, b;
	int n;
	cin >> a >> b >> n;
	point v = (b - a).unit();
	vector<point> points(n);
	ld low = 1e18, high = -1e18;
	for(point & p : points){
		cin >> p;
		p = p - a;
		ld t = p.dot(v);
		low = min(low, t);
		high = max(high, t);
	}
	low -= 10, high += 10;
	auto dist = [&](ld t){
		ld ans = 0;
		for(const point & p : points){
			ans += (p - v*t).length();
		}
		return ans;
	};
	while(true){
		if(abs(low - high) < 1e-8){
			ld t = (low + high) / 2;
			point r = a + v*t;
			cout << fixed << setprecision(8) << dist(t) << "\n" << r << "\n";
			break;
		}
		ld left_third = low + (high - low) / 3;
		ld right_third = high - (high - low) / 3;
		if(dist(left_third) > dist(right_third)){
			low = left_third;
		}else{
			high = right_third;
		}
	}
	return 0;
}