#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using ld = long double;

struct point{
	lli x, y;
	point(): x(0), y(0) {}
	point(lli x, lli y): x(x), y(y) {}

	point operator-(const point & p) const{
		return point(x - p.x, y - p.y);
	}

	lli dot(const point & p) const{
		return x*p.x + y*p.y;
	}

	lli cross(const point & p) const{
		return x*p.y - y*p.x;
	}

	ld length() const{
		return hypot(x, y);
	}

	point perpendicular() const{
		return point(-y, x);
	}

	bool operator<(const point & p) const{
		if(x == p.x) return y < p.y;
		return x < p.x;
	}
};

istream &operator>>(istream & is, point & p){
	is >> p.x >> p.y;
	return is;
}

ld distancePointLine(const point & a, const point & v, const point & p){
	return abs(v.cross(p - a)) / v.length();
}

vector<point> convexHull(vector<point> & P){
	sort(P.begin(), P.end());
	vector<point> L, U;
	for(int i = 0; i < P.size(); i++){
		while(L.size() >= 2 && (L[L.size() - 2] - P[i]).cross(L[L.size() - 1] - P[i]) <= 0){
			L.pop_back();
		}
		L.push_back(P[i]);
	}
	for(int i = P.size() - 1; i >= 0; i--){
		while(U.size() >= 2 && (U[U.size() - 2] - P[i]).cross(U[U.size() - 1] - P[i]) <= 0){
			U.pop_back();
		}
		U.push_back(P[i]);
	}
	L.pop_back();
	U.pop_back();
	L.insert(L.end(), U.begin(), U.end());
	return L;
}

ld smallestEnclosingRectangle(vector<point> & P){
	int n = P.size();
	auto dot = [&](int a, int b){return (P[(a+1)%n]-P[a]).dot(P[(b+1)%n]-P[b]);};
	auto cross = [&](int a, int b){return (P[(a+1)%n]-P[a]).cross(P[(b+1)%n]-P[b]);};
	ld area = numeric_limits<ld>::max();
	for(int i = 0, j = 0, k = 0, m = 0; i < n; ++i){
		while(dot(i, j) > 0) j = (j+1) % n;
		if(!i) k = j;
		while(cross(i, k) > 0) k = (k+1) % n;
		if(!i) m = k;
		while(dot(i, m) < 0) m = (m+1) % n;
		//pairs: (i, k) , (j, m)
		point v = P[(i+1)%n] - P[i];
		ld h = distancePointLine(P[i], v, P[k]);
		ld w = distancePointLine(P[j], v.perpendicular(), P[m]);
		area = min(area, h * w);
	}
	return area;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	while(cin >> n && n != 0){
		vector<point> polygon(n);
		for(auto & p : polygon) cin >> p;
		if(n < 3){
			cout << "0.000\n";
			continue;
		}
		polygon = convexHull(polygon);
		if(polygon.size() < 3){
			cout << "0.000\n";
			continue;
		}
		ld ans = smallestEnclosingRectangle(polygon);
		cout << fixed << setprecision(3) << ans << "\n";
	}
	return 0;
}