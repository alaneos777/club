#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct point{
	lli x, y;
	point(): x(0), y(0) {}
	point(lli x, lli y): x(x), y(y) {}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	lli cross(const point & p) const{return x * p.y - y * p.x;}
	lli norm() const{return x * x + y * y;}
	bool operator<(const point & p) const{return x < p.x || (x == p.x && y < p.y);}
	bool operator==(const point & p) const{return x == p.x && y == p.y;}
};

int sgn(lli x){
	if(x > 0) return 1;
	if(x < 0) return -1;
	return 0;
}

int pointInConvexPolygon(const vector<point> & P, const point & p, int right){
	if(p < P[0] || P[right] < p) return 0;
	int orientation = sgn((P[right] - P[0]).cross(p - P[0]));
	if(orientation == 0){
		if(p == P[0] || p == P[right]) return -1;
		return (right == 1 || right + 1 == P.size()) ? -1 : 1;
	}else if(orientation < 0){
		auto r = lower_bound(P.begin() + 1, P.begin() + right, p);
		int det = sgn((p - r[-1]).cross(r[0] - r[-1])) - 1;
		if(det == -2) det = 1;
		return det;
	}else{
		auto l = upper_bound(P.rbegin(), P.rend() - right - 1, p);
		int det = sgn((p - l[0]).cross((l == P.rbegin() ? P[0] : l[-1]) - l[0])) - 1;
		if(det == -2) det = 1;
		return det;
	}
}

istream &operator>>(istream & is, point & p){
	return is >> p.x >> p.y;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n;
	vector<point> A(n);
	for(point & a : A){
		cin >> a;
	}
	cin >> m;
	bool test = true;
	reverse(A.begin(), A.end());
	rotate(A.begin(), min_element(A.begin(), A.end()), A.end());
	int right = max_element(A.begin(), A.end()) - A.begin();
	for(int i = 0; i < m; ++i){
		point p;
		cin >> p;
		test &= pointInConvexPolygon(A, p, right) == 1;
	}
	if(test){
		cout << "YES\n";
	}else{
		cout << "NO\n";
	}
	return 0;
}