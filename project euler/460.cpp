#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using pt = pair<int, int>;
const double inf = 1e9;

double getTime(const pt & a, const pt & b){
	double dist = sqrt((a.first - b.first)*(a.first - b.first) + (a.second - b.second)*(a.second - b.second));
	double velocity = (a.second == b.second ? a.second : double(b.second - a.second) / (log(b.second) - log(a.second)));
	return dist / velocity;
}

int main(){
	int d = 10000;
	vector<pt> points;
	int start = -1, end = -1;
	for(int x = 0; x <= d; ++x){
		for(int y = 1; y <= d; ++y){
			double dif = abs(sqrt((x - d/2.0)*(x - d/2.0) + y*y) - sqrt((d/2.0)*(d/2.0) + 1));
			if(dif <= 0.25){
				if(x == 0 && y == 1){
					start = points.size();
				}else if(x == d && y == 1){
					end = points.size();
				}
				points.emplace_back(x, y);
			}
		}
	}
	int n = points.size();

	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> q;
	vector<double> times(n, inf);
	unordered_set<int> available;
	for(int i = 0; i < n; ++i){
		available.insert(i);
	}
	q.emplace(0, start);
	times[start] = 0;
	double ans = -1;
	while(!q.empty()){
		int u; double time_start_u;
		tie(time_start_u, u) = q.top();
		q.pop();
		if(u == end){
			ans = time_start_u;
			break;
		}
		if(times[u] < time_start_u) continue;
		available.erase(u);
		for(int v : available){
			double time_u_v = getTime(points[u], points[v]);
			double time_start_v = time_start_u + time_u_v;
			if(time_start_v < times[v]){
				times[v] = time_start_v;
				q.emplace(time_start_v, v);
			}
		}
	}

	cout << fixed << setprecision(9) << ans << "\n";
	return 0;
}