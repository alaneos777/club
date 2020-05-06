#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct point{
	lli x, y;
	point(): x(0), y(0) {}
	point(lli x, lli y): x(x), y(y) {}
	lli cross(const point & p) const{return x * p.y - y * p.x;}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<point> poly(n);
	for(point & p : poly){
		cin >> p.x >> p.y;
	}
	vector<lli> acum(2*n);
	for(int i = 1; i < 2*n; ++i){
		acum[i] = acum[i-1] + poly[(i-1)%n].cross(poly[i%n]);
	}
	lli total = abs(acum[n]);
	lli ans = 0;
	for(int i = 0; i < m; ++i){
		int l, r;
		cin >> l >> r;
		--l, --r;
		lli area = poly[r].cross(poly[l]);
		if(l > r) r += n;
		area += acum[r] - acum[l];
		area = abs(area);
		ans = max(ans, min(area, total - area));
	}
	cout << ans/2;
	if(ans & 1) cout << ".5";
	cout << "\n";
	return 0;
}