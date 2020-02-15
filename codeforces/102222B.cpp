#include <bits/stdc++.h>
using namespace std;
using ld = long double;

struct point{
	ld x, y;
	point(): x(0), y(0) {}
	point(ld x, ld y): x(x), y(y) {}
	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	ld cross(const point & p) const{return x * p.y - y * p.x;}
	ld dot(const point & p) const{return x * p.x + y * p.y;}
	ld length() const{return sqrtl(x*x + y*y);}
	point rotate(const ld & ang) const{return point(x * cosl(ang) - y * sinl(ang), x * sinl(ang) + y * cosl(ang));}
};

istream&operator>>(istream & is, point & p){
	return is >> p.x >> p.y;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	for(int caso = 1; caso <= t; ++caso){
		int n;
		cin >> n;
		vector<point> P(n);
		for(point & p : P){
			cin >> p;
		}
		point q;
		cin >> q;
		ld ans = 0;
		for(int i = 0; i < n; ++i){
			// edge P[i]->P[i+1], rotate everything around P[i+1]
			point u = P[(i+1)%n] - P[i];
			point v = P[(i+2)%n] - P[(i+1)%n];
			ld ang = acosl(u.dot(v) / u.length() / v.length());
			ans += (q - P[(i+1)%n]).length() * ang;
			q = (q - P[(i+1)%n]).rotate(ang) + P[(i+1)%n];
			for(int j = 0; j < n; ++j){
				if((i+1)%n == j) continue;
				P[j] = (P[j] - P[(i+1)%n]).rotate(ang) + P[(i+1)%n];
			}
		}
		cout << fixed << setprecision(3) << "Case #" << caso << ": " << ans << "\n";
	}
	return 0;
}