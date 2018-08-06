#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli inf = 1ll << 62;

struct point{
	lli x, y;
	bool operator<(const point & b) const{
		return y < b.y;
	}
};

bool comp1(const point & a, const point & b){
	return a.x < b.x;
}

lli dist(const point & a, const point & b){
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int r, m, n = 0, y;
	lli k;
	cin >> r >> k;
	vector<point> points;
	for(int x = 1; x <= r; ++x){
		cin >> m;
		for(int j = 0; j < m; ++j){
			cin >> y;
			points.push_back({x, y});
			++n;
		}
	}
	sort(points.begin(), points.end(), comp1);
	set<point> S;
	lli ans = inf;
	int pos = 0;
	for(int i = 0; i < n; ++i){
		while(pos < i && abs(points[i].x - points[pos].x) >= ans){
			S.erase(points[pos++]);
		}
		auto lower = S.lower_bound({-inf, points[i].y - ans});
		auto upper = S.upper_bound({-inf, points[i].y + ans});
		for(auto it = lower; it != upper; ++it){
			ans = min(ans, dist(points[i], *it));
		}
		S.insert(points[i]);
	}
	cout << k * ans << "\n";
	return 0;
}