#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using vec = vector<int>;
using mat = vector<vec>;
const int inf = 1e9;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, r;
	cin >> n >> m >> r;
	vector<mat> cars(m, mat(n, vec(n)));
	for(int c = 0; c < m; ++c){
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				cin >> cars[c][i][j];
			}
		}
		for(int l = 0; l < n; ++l){
			for(int i = 0; i < n; ++i){
				for(int j = 0; j < n; ++j){
					cars[c][i][j] = min(cars[c][i][j], cars[c][i][l] + cars[c][l][j]);
				}
			}
		}
	}
	vector<vector<tuple<int, int, int>>> queries(1001);
	vector<int> answers(r);
	for(int i = 0; i < r; ++i){
		int u, v, k;
		cin >> u >> v >> k;
		queries[k].emplace_back(u-1, v-1, i);
	}
	vector<mat> ans(2, mat(n, vec(n)));
	mat firstRow;
	for(int k = 0; k <= 1000; ++k){
		if(k == 0){
			for(int i = 0; i < n; ++i){
				for(int j = 0; j < n; ++j){
					int mini = inf;
					for(int c = 0; c < m; ++c){
						mini = min(mini, cars[c][i][j]);
					}
					ans[k&1][i][j] = mini;
				}
			}
			firstRow = ans[k&1];
		}else{
			for(int i = 0; i < n; ++i){
				for(int j = 0; j < n; ++j){
					int mini = inf;
					for(int l = 0; l < n; ++l){
						mini = min(mini, ans[(k-1)&1][i][l] + firstRow[l][j]);
					}
					ans[k&1][i][j] = mini;
				}
			}
		}
		for(auto[u, v, idx] : queries[k]){
			answers[idx] = ans[k&1][u][v];
		}
	}
	for(int qi : answers){
		cout << qi << "\n";
	}
	return 0;
}