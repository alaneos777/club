#include <bits/stdc++.h>
using namespace std;

double inf = 1e9;
double eps = 1e-9;

struct point{
	double x, y;
	bool operator<(const point & b) const{
		return y < b.y;
	}
};

bool comp1(const point & a, const point & b){
	return a.x < b.x;
}

double dist(const point & a, const point & b){
	return hypot(a.x - b.x, a.y - b.y);
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n;
	cin >> n;
	vector<point> points(n);
	for(int i = 0; i < n; ++i){
		cin >> points[i].x >> points[i].y;
	}
	sort(points.begin(), points.end(), comp1);
	set<point> S;
	double ans = inf;
	int pos = 0;
	for(int i = 0; i < n; ++i){
		while(pos < i && abs(points[i].x - points[pos].x) >= ans){
			S.erase(points[pos++]);
		}
		auto lower = S.lower_bound({-inf, points[i].y - ans - eps});
		auto upper = S.upper_bound({-inf, points[i].y + ans + eps});
		for(auto it = lower; it != upper; ++it){
			ans = min(ans, dist(points[i], *it));
		}
		S.insert(points[i]);
	}
	cout << fixed << setprecision(3) << ans << "\n";
	return 0;
}