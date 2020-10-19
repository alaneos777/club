#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct point{
	lli x, y;
	lli cross(const point & p) const{
		return x * p.y - y * p.x;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<point> p(n);
	for(point & pi : p){
		cin >> pi.x >> pi.y;
	}
	lli ans = 0;
	for(int i = 0; i < n; ++i){
		point a = p[i];
		point b = p[(i+1)%n];
		point c = p[(i+2)%n];
		ans += a.cross(b) + b.cross(c) + a.cross(c);
	}
	cout << fixed << setprecision(6) << ans/8.0l << "\n";
	return 0;
}