#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1008691207;

/*bool grid[100][100];

bool dfs(int n, int x, int y){
	if(x == n-1 && y == n-1) return true;
	bool ans = false;
	if(x+1 < n && grid[x+1][y]==0) ans |= dfs(n, x+1, y);
	if(y+1 < n && grid[x][y+1]==0) ans |= dfs(n, x, y+1);
	return ans;
}

int f(int n){
	int ans = 0;
	vector<int> pi(n);
	iota(pi.begin(), pi.end(), 0);
	do{
		memset(grid, 0, sizeof(grid));
		for(int i = 0; i < n; ++i){
			grid[i][pi[i]] = 1;
		}
		if(grid[0][0]==0 && dfs(n, 0, 0)){
			ans++;
		}
	}while(next_permutation(pi.begin(), pi.end()));
	return ans;
}*/

vector<int> fact;

int f(int n){
	int invalid = 0;
	for(int k = 1; k <= n-1; ++k){
		invalid += 2ll*fact[k] % mod;
		if(invalid >= mod) invalid -= mod;
	}
	invalid++;
	if(invalid >= mod) invalid -= mod;
	for(int i = 0; i <= n-2; ++i){
		invalid -= fact[i] * lli(n-1-i) % mod;
		if(invalid < 0) invalid += mod;
	}
	int ans = fact[n] - invalid;
	if(ans < 0) ans += mod;
	return ans;
}

int main(){
	int N = 1e8;
	fact.resize(N+1, 1);
	for(lli i = 2; i <= N; ++i){
		fact[i] = i*fact[i-1] % mod;
	}
	cout << f(N) << "\n";
	return 0;
}