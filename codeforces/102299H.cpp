#include <bits/stdc++.h>
using namespace std;

const int inf = numeric_limits<int>::max();

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> info(n, vector<int>(m, -1));
	for(int i = 0; i < n; ++i){
		int qi;
		cin >> qi;
		while(qi--){
			int g, c;
			cin >> c >> g;
			info[i][c-1] = g;
		}
	}
	for(int i = 0; i < n; ++i){
		pair<int, int> closest = {inf, inf};
		for(int j = 0; j < n; ++j){
			if(i == j) continue;
			int dist = 0, common = 0;
			for(int c = 0; c < m; ++c){
				if(info[i][c] != -1 && info[j][c] != -1){
					dist += (info[i][c] - info[j][c]) * (info[i][c] - info[j][c]);
					common++;
				}
			}
			if(common == 0) dist = inf;
			closest = min(closest, {dist, j});
		}
		int idx = closest.second;
		pair<int, int> recommend = {-inf, -inf};
		for(int c = 0; c < m; ++c){
			if(info[i][c] == -1 && info[idx][c] != -1){
				recommend = max(recommend, {info[idx][c], -c});
			}
		}
		if(recommend.first == -inf){
			cout << "-1\n";
		}else{
			cout << -recommend.second+1 << "\n";
		}
	}
	return 0;
}