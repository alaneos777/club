#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	int n = 1000;
	int t = 0;
	vector<int> s(n*(n+1)/2 + 1);
	for(int k = 1; k <= n*(n+1)/2; ++k){
		t = (615949*t + 797807) & ((1<<20) - 1);
		s[k] = t - (1 << 19);
	}
	auto idx = [&](int r, int c){
		return r*(r-1)/2 + c;
	};
	vector<vector<int>> cols(n+1, vector<int>(n+1));
	vector<vector<int>> diags(n+1, vector<int>(n+1));
	for(int c = 1; c <= n; ++c){
		for(int r = c; r <= n; ++r){
			cols[c][r] = s[idx(r, c)] + cols[c][r-1];
		}
	}
	for(int d = 1; d <= n; ++d){
		for(int i = 1; i <= n-d+1; ++i){
			diags[d][i] = s[idx(d+i-1, i)] + diags[d][i-1];
		}
	}
	int ans = 2e9;
	for(int i = 1; i < n; ++i){
		for(int j = i; j <= n; ++j){
			int sz = j-i+1;
			int sum = 0;
			for(int k = 1; k <= sz; ++k){
				sum += cols[k][j] - cols[k][i+k-2];
			}
			ans = min(ans, sum);
			for(int k = 1; k <= i; ++k){
				sum = sum - (cols[k][j] - cols[k][i-1]) + (diags[i-k][sz+k] - diags[i-k][k]);
				ans = min(ans, sum);
			}
		}
	}
	cout << ans << "\n";
	return 0;
}