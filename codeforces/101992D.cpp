#include <bits/stdc++.h>
using namespace std;

auto sieve(int n){
	vector<int> primes, f(n+1);
	f[1] = 1;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]){
			primes.push_back(i);
			f[i] = 1-i;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0){
				f[d] = f[i];
				break;
			}else{
				f[d] = f[i] * f[p];
			}
		}
	}
	return f;
}

const int M = 1e5;
const auto f = sieve(M);
const int mod = 1e9 + 7;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	freopen("lcm.in", "r", stdin);
	vector<int> inv(M+1, 1);
	for(int64_t i = 2; i <= M; ++i){
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
	}
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		vector<int> a(n);
		int MAX = 0;
		for(int & ai : a){
			cin >> ai;
			MAX = max(MAX, ai);
		}
		vector<int> freq(MAX+1), cnt(MAX+1);
		for(int ai : a){
			freq[ai] += ai;
		}
		for(int i = 1; i <= MAX; ++i){
			for(int j = i; j <= MAX; j += i){
				(cnt[i] += freq[j]) %= mod;
			}
		}
		int ans = 0;
		for(int i = 1; i <= MAX; ++i){
			ans += (int64_t)inv[i] * f[i] % mod * cnt[i] % mod * cnt[i] % mod;
			if(ans >= mod) ans -= mod;
			if(ans < 0) ans += mod;
		}
		cout << ans << "\n";
	}
	return 0;
}