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

	lli cross(const point & p) const{
		return x * p.y - y * p.x;
	}

	long double length() const{
		return hypotl(x, y);
	}
};

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

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n;
		long double l;
		cin >> n >> l;
		vector<point> polygon(n);
		for(int i = 0; i < n; ++i){
			polygon[i].read();
		}
		reverse(polygon.begin(), polygon.end());
		polygon = convexHull(polygon);
		n = polygon.size();
		long double ans = 2 * acosl(-1.0l) * l;
		for(int i = 0; i < n; ++i){
			ans += (polygon[(i+1)%n] - polygon[i]).length();
		}
		long double p = round(ans);
		cout << (lli)p << "\n";
		if(t) cout << "\n";
	}
	return 0;
}