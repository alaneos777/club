#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct point{
	lli x, y;
	point(): x(0), y(0){}
	point(lli x, lli y): x(x), y(y) {}
	point operator-(const point& p) const{return point(x - p.x, y - p.y);}
	lli dot(const point& p) const{return x * p.x + y * p.y;}
	lli cross(const point& p) const{return x * p.y - y * p.x;}
	bool operator==(const point& p) const{return x == p.x && y == p.y;}
	bool half(const point& p) const{
		return p.cross(*this) < 0 || (p.cross(*this) == 0 && p.dot(*this) > 0);
	}
};

istream& operator>>(istream& is, point& p){
	return is >> p.x >> p.y;
}

ostream& operator<<(ostream& os, const point& p){
	return os << p.x << " " << p.y;
}

void polarSort(vector<point> & P, const point & o, const point & v){
	//sort points in P around o, taking the direction of v as first angle
	sort(P.begin(), P.end(), [&](const point & a, const point & b){
		bool h1 = (a - o).half(v);
		bool h2 = (b - o).half(v);
		if(h1 != h2) return h1 < h2;
		if(a == o) return false;
		if(b == o) return true;
		return (a - o).cross(b - o) > 0;
	});
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<point> P(n);
	for(point& p : P){
		cin >> p;
	}
	polarSort(P, {0, 0}, {-1, 0});
	for(point p : P){
		cout << p << "\n";
	}
	return 0;
}