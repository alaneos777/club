#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	int n, W, V = 0;
	cin >> n >> W;
	vector<int> w(n), v(n);
	for(int i = 0; i < n; ++i){
		cin >> w[i] >> v[i];
		V += v[i];
	}

	vector<vector<int>> mem(n+1, vector<int>(V+1, -1));
	function<int(int, int)> dp = [&](int pos, int rem){
		if(rem <= 0) return 0;
		if(pos == n) return 1<<30;
		if(mem[pos][rem] != -1) return mem[pos][rem];
		int ans = min(dp(pos + 1, rem), w[pos] + dp(pos + 1, rem - v[pos]));
		return mem[pos][rem] = ans;
	};

	for(int i = V; i >= 0; --i){
		if(dp(0, i) <= W){
			cout << i << "\n";
			break;
		}
	}
	return 0;
}