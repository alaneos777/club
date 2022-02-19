#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct point{
	int x, y;
	point(): x(0), y(0){}
	point(int x, int y): x(x), y(y){}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	int cross(const point & p) const{return x*p.y - y*p.x;}
	bool operator<(const point & p) const{
		if(x != p.x) return x < p.x;
		return y < p.y;
	}
};

istream&operator>>(istream & is, point & p){
	return is >> p.x >> p.y;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	lli ans = lli(n) * (n-1) * (n-2) / 6;
	vector<point> points(n);
	for(point & p : points){
		cin >> p;
	}
	map<tuple<int, int, int>, set<point>> lines;
	for(int i = 0; i < n; ++i){
		for(int j = i+1; j < n; ++j){
			point v = points[j] - points[i];
			int a = v.y;
			int b = -v.x;
			int c = points[i].cross(v);
			int d = __gcd(__gcd(abs(a), abs(b)), abs(c));
			a /= d, b /= d, c /= d;
			if(a < 0){
				a = -a, b = -b, c = -c;
			}else if(a == 0){
				if(b < 0){
					b = -b, c = -c;
				}
			}
			auto & line = lines[{a, b, c}];
			line.insert(points[i]);
			line.insert(points[j]);
		}
	}
	for(const auto & p : lines){
		int sz = p.second.size();
		ans -= (lli)sz * (sz-1) * (sz-2) / 6;
	}
	cout << ans << "\n";
	return 0;
}