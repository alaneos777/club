#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int aleatorio(int a, int b){
	uniform_int_distribution<int> dist(a, b);
	return dist(rng);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<lli> a(n);
	for(lli& ai : a){
		cin >> ai;
	}
	lli ans = 0;
	map<lli, int> mp;
	vector<lli> keys;
	vector<int> vals;
	for(int r = 1; r <= 15; ++r){
		mp.clear(); keys.clear(); vals.clear();
		lli x = a[aleatorio(0, n-1)];
		for(lli ai : a){
			mp[__gcd(ai, x)]++;
		}
		for(const auto&[k, v] : mp){
			keys.push_back(k);
			vals.push_back(v);
		}
		int s = mp.size();
		for(int i = 0; i < s; ++i){
			int cnt = 0;
			lli u = keys[i];
			for(int j = i; j < s; ++j){
				lli v = keys[j];
				if(v%u == 0) cnt += vals[j];
			}
			if(2*cnt >= n){
				ans = max(ans, u);
			}
		}
	}
	cout << ans << "\n";
	return 0;
}