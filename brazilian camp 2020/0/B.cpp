#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;
const int M = 1e7 + 100;

vector<int> fact, inv, invfact;

void calc(int n){
	fact.resize(n+1, 1), inv.resize(n+1, 1), invfact.resize(n+1, 1);
	for(int i = 2; i <= n; ++i){
		fact[i] = (lli)fact[i-1] * i % mod;
		inv[i] = mod - (mod/i) * inv[mod%i] % mod;
		invfact[i] = (lli)invfact[i-1] * inv[i] % mod;
	}
}

lli ncr(int n, int k){
	if(k < 0 || k > n) return 0;
	return (lli)fact[n] * invfact[k] % mod * invfact[n - k] % mod;
}

map<int, lli> mult(const map<int, lli> & a, const map<int, lli> & b, int n){
	map<int, lli> c;
	for(const auto & ai : a){
		for(const auto & bi : b){
			if(ai.first + bi.first <= n){
				(c[ai.first + bi.first] += ai.second * bi.second) %= mod;
			}
		}
	}
	return c;
}

vector<int> getDivs(int m){
	vector<int> ans;
	for(int i = 1; i*i <= m; ++i){
		if(m % i != 0) continue;
		int j = m/i;
		ans.push_back(i);
		if(j != i) ans.push_back(j);
	}
	return ans;
}

int phi(int n){
	int ans = n;
	for(int p = 2; p*p <= n; ++p){
		if(n % p == 0){
			while(n % p == 0) n /= p;
			ans -= ans / p;
		}
	}
	if(n > 1) ans -= ans / n;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	calc(M);
	int t;
	cin >> t;
	while(t--){
		int n, m;
		cin >> n >> m;
		lli ans = 0;
		int lim = (n-1) / 2;

		//rotations
		auto divs = getDivs(m);
		for(int d : divs){
			lli term = 0;
			int len = m/d;
			if(n % len != 0) continue;
			int pot = n/len, i = 0;
			while(i <= d && pot >= 1){
				term += ncr(pot-1, d-1) * ncr(d, i) % mod * ((i&1) ? mod-1 : 1) % mod;
				if(term >= mod) term -= mod;
				pot -= lim;
				i++;
			}
			ans += term * phi(len) % mod;
			if(ans >= mod) ans -= mod;
		}

		//reflections
		if(m & 1){
			int a = lim, b = 2*lim;
			int pot = 0, i = 0, d = (m-1)/2;
			map<int, lli> P;
			while(i <= d && pot <= n){
				P[pot] = ncr(d, i) * ((i&1) ? mod-1 : 1) % mod;
				pot += b;
				i++;
			}
			P = mult(P, {{0, 1}, {a, -1+mod}}, n);
			lli term = 0;
			for(const auto & par : P){
				int q = n - par.first;
				if(q >= m){
					term += par.second * ncr((q-m)/2 + d, d) % mod;
					if(term >= mod) term -= mod;
				}
			}
			ans += term * m % mod;
			if(ans >= mod) ans -= mod;
		}else{
			int a = lim, b = 2*lim;
			int pot = 0, i = 0, d = m/2 - 1;
			map<int, lli> P;
			while(i <= d && pot <= n){
				P[pot] = ncr(d, i) * ((i&1) ? mod-1 : 1) % mod;
				pot += b;
				i++;
			}
			P = mult(P, {{0, 1}, {a, -2+mod}, {2*a, 1}}, n);
			lli term = 0;
			for(const auto & par : P){
				int q = n - par.first;
				if(q >= m){
					lli tmp = 2*ncr((q-m)/2 + m/2, m/2) % mod;
					if((q-m) % 2 == 0){
						tmp -= ncr(q/2-1, m/2-1);
						if(tmp < 0) tmp += mod;
					}
					term += par.second * tmp % mod;
					if(term >= mod) term -= mod;
				}
			}
			if(n % 2 == 0){
				term += ncr(n/2-1, m/2-1);
				if(term >= mod) term -= mod;
			}
			ans += term * (m/2) % mod;
			if(ans >= mod) ans -= mod;
		}

		ans = ans * inv[2] % mod * inv[m] % mod;
		cout << ans << "\n";
	}
	return 0;
}