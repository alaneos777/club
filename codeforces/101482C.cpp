#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, d;
	cin >> n >> d;
	vector<int> a(n), b(n);
	for(int & ai : a){
		cin >> ai;
	}
	partial_sum(a.begin(), a.end(), b.begin());
	auto Rnd = [&](int x){
		return 10 * ((x + 5) / 10);
	};
	auto get = [&](int l, int r){
		return Rnd(b[r] - (l-1 >= 0 ? b[l-1] : 0));
	};
	vector<vector<int>> mem(n+1, vector<int>(d+2, -1));
	function<int(int, int)> f = [&](int pos, int rem){
		if(pos == n){
			return 0;
		}else if(rem == 1){
			return get(pos, n-1);
		}else{
			int & ans = mem[pos][rem];
			if(ans != -1) return ans;
			ans = 1e9;
			for(int i = pos; i < n; ++i){
				ans = min(ans, get(pos, i) + f(i+1, rem-1));
			}
			return ans;
		}
	};
	cout << f(0, d+1) << "\n";
	return 0;
}