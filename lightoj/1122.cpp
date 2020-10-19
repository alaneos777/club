#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

lli mem[15][10];

lli dp(int pos, int last_digit, int n, const vector<int> & allowed){
	if(pos == n){
		return 1;
	}
	lli & ans = mem[pos][last_digit];
	if(ans != -1) return ans;
	ans = 0;
	for(int d : allowed){
		if(pos == 0 || abs(d - last_digit) <= 2){
			ans += dp(pos + 1, d, n, allowed);
		}
	}
	return ans;
}

lli f(int n, const vector<int> & allowed){
	memset(mem, -1, sizeof(mem));
	return dp(0, 0, n, allowed);
}

int main(){
	//ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	for(int c = 1; c <= t; ++c){
		int m, n;
		cin >> m >> n;
		vector<int> allowed(m);
		for(int & di : allowed){
			cin >> di;
		}
		cout << "Case " << c << ": " << f(n, allowed) << "\n";
	}
	return 0;
}