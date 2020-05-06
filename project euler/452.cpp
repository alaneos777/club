#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1234567891;

vector<int> sieve(int n){
	vector<int> lp(n+1, 1);
	lp[0] = lp[1] = 0;
	for(int i = 2; i <= n; ++i) lp[i] = (i&1 ? i : 2);
	for(int i = 3; i*i <= n; i += 2){
		if(lp[i] == i){
			for(int j = i*i; j <= n; j += 2*i){
				if(lp[j] == j) lp[j] = i;
			}
		}
	}
	return lp;
}

const int M = 1e9, N = 1e9;

const auto lp = sieve(M+1);

vector<int> fact(int n){
	vector<int> ans;
	while(n > 1){
		int p = lp[n];
		int cnt = 0;
		while(n % p == 0){
			n /= p;
			cnt++;
		}
		ans.push_back(cnt);
	}
	sort(ans.begin(), ans.end());
	return ans;
}

lli getHash(const vector<int> & f){
	lli ans = 0;
	for(int e : f){
		ans = ans * 100 + e;
	}
	return ans;
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

lli ncr(lli n, lli r){
	if(r < 0 || r > n) return 0;
	r = min(r, n - r);
	lli ans = 1;
	for(lli den = 1, num = n; den <= r; den++, num--){
		ans = ans * num % mod * power(den, mod - 2) % mod;
	}
	return ans;
}

int main(){
	map<lli, lli> mem;
	vector<lli> mem2(100, -1);
	lli ans = 0;
	for(int m = 1; m <= M; ++m){
		auto f = fact(m);
		lli hash = getHash(f);
		lli term = 1;
		if(mem.count(hash)){
			term = mem[hash];
		}else{
			for(int e : f){
				if(mem2[e] == -1){
					mem2[e] = ncr(N - 1 + e, N - 1);
				}
				term = term * mem2[e] % mod;
			}
			mem[hash] = term;
		}
		ans += term;
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}