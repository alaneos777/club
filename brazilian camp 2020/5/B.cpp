#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;

struct point{
	ll x, y;
	point(): x(0), y(0) {}
	point(ll x, ll y): x(x), y(y) {}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	ll cross(const point & p) const{return x*p.y - y*p.x;}
	ld length() const{return sqrtl(x*x + y*y);}
	bool operator<(const point & p) const{
		if(x != p.x) return x < p.x;
		return y < p.y;
	}
	bool operator==(const point & p) const{return x==p.x && y==p.y;}
};

istream&operator>>(istream & is, point & p){
	return is >> p.x >> p.y;
}

vector<point> ch(vector<point> & p){
	sort(p.begin(), p.end());
	p.erase(unique(p.begin(), p.end()), p.end());
	int n = p.size();
	if(n <= 2) return p;
	bool line = true;
	for(int i = 2; i < n; ++i){
		line &= ((p[i] - p[0]).cross(p[1] - p[0]) == 0);
	}
	if(line) return p;
	vector<point> L, U;
	for(int i = 0; i < n; ++i){
		while(L.size() >= 2 && (L[L.size()-2] - p[i]).cross(L[L.size()-1] - p[i]) < 0)
			L.pop_back();
		L.push_back(p[i]);
	}
	for(int i = n-1; i >= 0; --i){
		while(U.size() >= 2 && (U[U.size()-2] - p[i]).cross(U[U.size()-1] - p[i]) < 0)
			U.pop_back();
		U.push_back(p[i]);
	}
	L.pop_back(), U.pop_back();
	U.insert(U.end(), L.begin(), L.end());
	return U;
}

ld ans[2600][2600][2];

ld dp(int i, int j, bool f, const vector<point> & p){
	int n = p.size();
	if((j+1)%n == i) return 0;
	if(ans[i][j][f] != -1) return ans[i][j][f];
	int idx = (f ? j : i);
	int prev = (i - 1 + n) % n;
	int next = (j + 1) % n;
	ld dist = min((p[prev] - p[idx]).length() + dp(prev, j, false, p), (p[next] - p[idx]).length() + dp(i, next, true, p));
	return ans[i][j][f] = dist;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for(int i = 0; i < 2600; ++i)
		for(int j = 0; j < 2600; ++j)
			for(int k = 0; k < 2; ++k)
				ans[i][j][k] = -1;
	cout << fixed << setprecision(11);
	int n;
	cin >> n;
	vector<point> p(n);
	for(point & pt : p){
		cin >> pt;
	}
	p = ch(p);
	n = p.size();
	ld ans = 1e18;
	for(int i = 0; i < n; ++i){
		ans = min(ans, dp(i, i, false, p));
	}
	cout << ans << "\n";
	return 0;
}