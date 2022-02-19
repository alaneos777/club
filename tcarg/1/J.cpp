#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> shelves(n);
	for(int i = 0; i < n; ++i){
		int sz;
		cin >> sz;
		shelves[i] = vector<int>(sz+1);
		for(int j = 1; j <= sz; ++j){
			cin >> shelves[i][j];
		}
		partial_sum(shelves[i].begin(), shelves[i].end(), shelves[i].begin());
	}
	vector<vector<int>> M(n, vector<int>(111));
	for(int i = 0; i < n; ++i){
		int sz = shelves[i].size()-1;
		for(int j = 0; j <= sz; ++j){
			for(int k = 0; k <= j; ++k){
				int d = j-k;
				M[i][j] = max(M[i][j], shelves[i][sz] - shelves[i][sz-d] + shelves[i][k]);
			}
		}
	}
	vector<vector<int>> f(n, vector<int>(11111));
	for(int i = 0; i < n; ++i){
		for(int j = m; j > 0; --j){
			for(int k = 0; k <= j && k < shelves[i].size(); ++k){
				f[i][j] = max(f[i][j], (i ? f[i-1][j-k] : 0) + M[i][k]);
			}
		}
	}
	cout << f[n-1][m] << "\n";
	return 0;
}