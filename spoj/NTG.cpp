#include <bits/stdc++.h>
using namespace std;
typedef long long int ull;

vector<int> primos;

void criba(int n){
	primos.push_back(2);
	vector<bool> es_primo(n + 1, true);
	int limit = sqrt(n);
	for(int i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			if(i <= limit){
				for(int j = i * i; j <= n; j += 2 * i){
					es_primo[j] = false;
				}
			}
		}
	}
}

ull mod = 1e9 + 7;

ull exp_bin(ull a, int b, ull m){
	ull ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		if(b) a = a * a % m;
	}
	return ans;
}

ull inv(ull a, ull m){
	ull r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	assert(abs(r0) == 1);
	if(r0 == -1) s0 *= -1;
	if(s0 < 0) s0 += m;
	return s0;
}

ull suma_gcd(int n, int k){
	if(n == 0) return 0;
	vector<pair<int, int>> fact;
	for(int & p : primos){
		if(p * p > n) break;
		if(n % p == 0){
			int pot = 0;
			while(n % p == 0){
				n /= p;
				++pot;
			}
			fact.push_back({p, pot});
		}
	}
	if(n > 1){
		fact.push_back({n, 1});
	}
	ull ans = 1;
	for(auto & f : fact){
		int p = f.first, a = f.second;
		ull tmp = 0;
		ull p_a = exp_bin(p, a, mod);
		ull p_k = exp_bin(p, k, mod);
		ull p_ak = exp_bin(p_a, k, mod);
		if(k == 1){
			tmp = p_a * (1 + (p - 1) * a % mod * inv(p, mod) % mod) % mod;
		}else{
			tmp = (p_ak + (p - 1) * (p_ak - p_a) % mod * inv(p_k - p, mod) % mod) % mod;
		}
		ans = ans * tmp % mod;
	}
	if(ans < 0) ans += mod;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int limit = 1e5;
	criba(sqrt(limit));
	int k, t, l, r;
	cin >> k >> t;
	vector<ull> valores(limit + 1);
	for(int i = 1; i <= limit; ++i){
		valores[i] = (valores[i - 1] + suma_gcd(i, k)) % mod;
	}
	while(t--){
		cin >> l >> r;
		ull ans = (valores[r] - valores[l - 1]) % mod;
		if(ans < 0) ans += mod;
		cout << ans << "\n";
	}
	return 0;
}