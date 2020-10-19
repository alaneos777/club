#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

const lli inf = 1e18;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<lli> a(n);
	for(lli & ai : a){
		cin >> ai;
	}
	auto query_max = [&](int l, int r){
		unordered_map<lli, int> freq;
		for(int i = l; i <= r; ++i){
			freq[a[i]]++;
		}
		int maxi = 0;
		lli ans = 0;
		for(const auto & par : freq){
			if(par.second > maxi){
				maxi = par.second;
				ans = par.first;
			}else if(par.second == maxi){
				if(par.first > ans){
					ans = par.first;
				}
			}
		}
		return ans;
	};
	auto query_min = [&](int l, int r){
		unordered_map<lli, int> freq;
		for(int i = l; i <= r; ++i){
			freq[a[i]]++;
		}
		int mini = 1e9;
		lli ans = 0;
		for(const auto & par : freq){
			if(par.second < mini){
				mini = par.second;
				ans = par.first;
			}else if(par.second == mini){
				if(par.first < ans){
					ans = par.first;
				}
			}
		}
		return ans;
	};
	vector<vector<lli>> mem(n+1, vector<lli>(k+1));
	vector<vector<bool>> calc(n+1, vector<bool>(k+1));
	function<lli(int, int)> f = [&](int pos, int rem){
		if(pos == n){
			return 0ll;
		}else if(rem == 1){
			return query_max(pos, n-1) - query_min(pos, n-1);
		}else{
			lli & ans = mem[pos][rem];
			if(calc[pos][rem]) return ans;
			calc[pos][rem] = true;
			for(int i = pos; i < n; ++i){
				lli take = query_max(pos, i) - query_min(pos, i) + f(i+1, rem-1);
				if(i == pos || take > ans){
					ans = take;
				}
			}
			return ans;
		}
	};
	cout << f(0, k) << "\n";
	return 0;
}