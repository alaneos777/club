#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> ans(n, vector<int>(m));
	vector<int> rows(n), cols(m);
	for(int i = 0; i < n; ++i) cin >> rows[i];
	for(int j = 0; j < m; ++j) cin >> cols[j];
	auto tryFill = [&](int r, int c){
		vector<vector<int>> mat(n, vector<int>(m));
		int col = cols[c], row = rows[r];
		for(int i = 0; i < n; ++i){
			if(i != r){
				mat[i][c] = rows[i];
				col ^= rows[i];
			}
		}
		for(int j = 0; j < m; ++j){
			if(j != c){
				mat[r][j] = cols[j];
				row ^= cols[j];
			}
		}
		if(col != row) return false;
		mat[r][c] = col;
		cout << "YES\n";
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < m; ++j){
				cout << mat[i][j] << " ";
			}
			cout << "\n";
		}
		return true;
	};
	for(int r = 0; r < n; ++r){
		for(int c = 0; c < m; ++c){
			if(tryFill(r, c)){
				exit(0);
			}
		}
	}
	cout << "NO\n";
	return 0;
}