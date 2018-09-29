#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

struct point{
	lli x, y;
	point(): x(0), y(0){}
	point(lli x, lli y): x(x), y(y){}
	void read(){cin >> x >> y;}
};

struct edge{
	int dest;
	lli cost;
	edge(): dest(0), cost(0){}
	edge(lli dest, lli cost): dest(dest), cost(cost){}
};

lli dist(const point & a, const point & b){
	return abs(a.x - b.x) + abs(a.y - b.y);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<point> students(n), tutors(n);
	for(int i = 0; i < n; ++i){
		students[i].read();
	}
	for(int i = 0; i < n; ++i){
		tutors[i].read();
	}
	vector<vector<edge>> graph(n);
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			graph[i].emplace_back(j, dist(students[i], tutors[j]));
		}
	}

	function<int(int, int, lli)> maxMatching = [&](int l, int r, lli limit){
		vector<int> left(l, -1), right(r, -1);
		vector<bool> used(l);

		function<bool(int)> tryKuhn = [&](int u){
			if(used[u]) return false;
			used[u] = true;
			for(edge & current : graph[u]){
				if(current.cost > limit) continue;
				int v = current.dest;
				if(right[v] == -1 || tryKuhn(right[v])){
					right[v] = u;
					left[u] = v;
					return true;
				}
			}
			return false;
		};

		for(int u = 0; u < l; ++u){
			tryKuhn(u);
			fill(used.begin(), used.end(), false);
		}
		int cnt = 0;
		vector<pair<int, int>> ans;
		for(int u = 0; u < r; ++u){
			if(right[u] != -1){
				++cnt;
			}
		}
		return cnt == n;
	};

	lli l = 0, r = 1e9, m = 0;
	while(true){
		m = l + (r - l) / 2;
		if(maxMatching(n, n, m)){
			if(maxMatching(n, n, m - 1)){
				r = m - 1;
			}else{
				break;
			}
		}else{
			l = m + 1;
		}
	}

	cout << m << "\n";

	return 0;
}