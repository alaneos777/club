#include <bits/stdc++.h>
using namespace std;

int inf = 1 << 29;

int n, m;
vector<vector<vector<int>>> mem;
vector<vector<char>> tablero;

int dp(int i, int j, int mask){
	cout << "(" << i << ", " << j << ", " << mask << ")\n";
	if(i > n) return -inf;
	int nf = i, nc = j + 1;
	if(nc > m){
		nc = 1;
		nf++;
	}
	if(nf <= n && tablero[nf][nc] == '.'){
		int ans = min(dp(nf, nc, ~(1 << j) & mask) + 1, dp(nf, nc, (1 << j) | mask) + 1);
		if((mask & (1 << j)) == 0){
			ans = min(ans, dp(nf, nc, mask));
		}
		if((mask & (1 << (j - 1))) == 1){
			ans = min(ans, dp(nf, nc, (1 << j) | mask));
		}
	}else{
		return dp(nf, nc, mask);
	}
}

int main(){
	//ios_base::sync_with_stdio(0);
	//cin.tie(0);
	cin >> n >> m;
	tablero.resize(n + 1, vector<char>(m + 1, 0));
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin >> tablero[i][j];
		}
	}
	mem.resize(n + 2, vector<vector<int>>(m + 2, vector<int>(520, -1)));
	cout << dp(1, 1, 0);
	return 0;
}