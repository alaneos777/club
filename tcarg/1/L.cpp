#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

map<pair<int, int>, lli> mem[2222];

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<lli> a(n), b(n);
	for(lli& ai : a){
		cin >> ai;
	}
	for(lli& bi : b){
		cin >> bi;
	}
	lli inf = 1e18;
	function<lli(int, int, int)> f = [&](int pos, int bal, int rem){
		if(pos == n){
			if(bal == 0 && rem == 0) return 0ll;
			else return inf;
		}else{
			if(mem[pos].count({bal, rem})) return mem[pos][{bal, rem}];
			lli ans = f(pos+1, bal, rem);
			// print
			if(bal > 0){
				ans = min(ans, f(pos+1, bal-1, rem) + b[pos]);
			}
			// prepare
			if(rem > 0 && bal < k){
				ans = min(ans, f(pos+1, bal+1, rem-1) + a[pos]);
			}
			// prepare and print
			if(rem > 0){
				ans = min(ans, f(pos+1, bal, rem-1) + a[pos] + b[pos]);
			}
			return mem[pos][{bal, rem}] = ans;
		}
	};
	return 0;
}