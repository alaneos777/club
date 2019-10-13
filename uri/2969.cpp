#include <bits/stdc++.h>
using namespace std;

const int inf = numeric_limits<int>::max();

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, r, q;
	cin >> n >> r;
	vector<pair<int, int>> temps(n);
	for(int i = 0; i < n; ++i){
		cin >> temps[i].first;
		temps[i].second = i;
	}
	vector<vector<int>> mat(n, vector<int>(n, inf));
	for(int i = 0; i < r; ++i){
		int x, y, d;
		cin >> x >> y >> d;
		mat[x-1][y-1] = d;
		mat[y-1][x-1] = d;
	}
	cin >> q;
	vector<vector<vector<tuple<int, int, int>>>> queries(2, vector<vector<tuple<int, int, int>>>(n));
	vector<int> ans(q, inf);
	for(int i = 0; i < q; ++i){
		int a, b, k, t;
		cin >> a >> b >> k >> t;
		queries[t][k-1].push_back({a-1, b-1, i});
	}
	auto floyd = [&](int t){
		if(t == 0){
			sort(temps.begin(), temps.end());
		}else{
			sort(temps.begin(), temps.end(), greater<pair<int, int>>());
		}
		auto tmp = mat;
		int prev = temps[0].first;
		int w = 0;
		for(int pos = 0; pos <= n; ++pos){
			if(pos == n || temps[pos].first != prev) {
				for(auto query : queries[t][w]){
					int a, b, i;
					tie(a, b, i) = query;
					ans[i] = tmp[a][b];
				}
				w++;
				if(pos == n) break;
			}
			int k = temps[pos].second;
			for(int i = 0; i < n; ++i){
				for(int j = 0; j < n; ++j){
					if(tmp[i][k] == inf || tmp[k][j] == inf) continue;
					tmp[i][j] = min(tmp[i][j], tmp[i][k] + tmp[k][j]);
				}
			}
			prev = temps[pos].first;
		}
		while(w < n){
			for(auto query : queries[t][w]){
				int a, b, i;
				tie(a, b, i) = query;
				ans[i] = tmp[a][b];
			}
			w++;
		}
	};
	floyd(1);
	floyd(0);
	for(int i = 0; i < q; ++i){
		if(ans[i] == inf) cout << "-1\n";
		else cout << ans[i] << "\n";
	}
	return 0;
}