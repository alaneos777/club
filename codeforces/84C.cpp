#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

struct circle{
	lli x, r;
};

struct point{
	lli x, y;
	int id;
	point(): x(0), y(0), id(0) {}
	point(lli x, lli y): x(x), y(y), id(0) {}

	bool operator<(const point & p) const{
		return x < p.x || (x == p.x && y < p.y);
	}
};

const lli inf = 1e9;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n;
	vector<circle> circles(n);
	for(circle & ci : circles){
		cin >> ci.x >> ci.r;
	}
	cin >> m;
	vector<point> shots(m);
	for(int i = 0; i < m; ++i){
		cin >> shots[i].x >> shots[i].y;
		shots[i].id = i+1;
	}
	sort(shots.begin(), shots.end());
	vector<int> ans(n, -1);
	int cnt = 0;
	for(int i = 0; i < n; ++i){
		int mini = inf;
		lli r = circles[i].r;
		lli pos = circles[i].x;
		lli x0 = pos - r;
		lli x1 = pos + r;
		int start = lower_bound(shots.begin(), shots.end(), point(x0, -inf)) - shots.begin();
		int end = lower_bound(shots.begin(), shots.end(), point(x1, inf)) - shots.begin();
		for(; start < end; ++start){
			if((shots[start].x - pos) * (shots[start].x - pos) + shots[start].y * shots[start].y <= r*r){
				mini = min(mini, shots[start].id);
			}
		}
		if(mini != inf){
			ans[i] = mini;
			cnt++;
		}
	}
	cout << cnt << "\n";
	for(int ai : ans){
		cout << ai << " ";
	}
	cout << "\n";
	return 0;
}