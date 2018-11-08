#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct point{
	lli x, y;
	point(): x(0), y(0) {}
	point(lli x, lli y): x(x), y(y) {}
	void read(){cin >> x >> y;}
	lli cross(const point & p) const{
		return x * p.y - y * p.x;
	}
	point operator-(const point & p) const{
		return point(x - p.x, y - p.y);
	}
	bool operator<(const point & p) const{
		if(x == p.x) return y < p.y;
		return x < p.x;
	}
	lli sqlength() const{
		return x*x + y*y;
	}
};

vector<point> process(vector<point> & P){
	int n = P.size();
	rotate(P.begin(), min_element(P.begin(), P.end()), P.end());
	vector<point> seg(n - 1);
	for(int i = 0; i < n - 1; ++i)
		seg[i] = P[i + 1] - P[0];
	return seg;
}

lli sgn(lli x){
	if(x > 0) return 1;
	if(x < 0) return -1;
	return 0;
}

bool pointInConvexPolygon(vector<point> & seg, const point & p){
	int n = seg.size();
	if(seg[0].cross(p) != 0 && sgn(seg[0].cross(p)) != sgn(seg[0].cross(seg[n - 1])))
		return false;
	if(seg[n - 1].cross(p) != 0 && sgn(seg[n - 1].cross(p)) != sgn(seg[n - 1].cross(seg[0])))
		return false;
	if(seg[0].cross(p) == 0)
		return seg[0].sqlength() >= p.sqlength();
	int l = 0, r = n - 1;
	while(r - l > 1){
		int m = (l + r) / 2;
		if(seg[m].cross(p) >= 0) l = m;
		else r = m;
	}
	return abs(seg[l].cross(seg[l + 1])) == abs((p - seg[l]).cross(p - seg[l + 1])) + abs(p.cross(seg[l])) + abs(p.cross(seg[l + 1]));
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	vector<point> polygon(n);
	for(auto & p : polygon) p.read();
	vector<point> seg = process(polygon);
	int cnt = 0;
	while(m--){
		point p;
		p.read();
		cnt += pointInConvexPolygon(seg, p - polygon[0]);
	}
	if(cnt >= k) cout << "YES\n";
	else cout << "NO\n";
	return 0;
}