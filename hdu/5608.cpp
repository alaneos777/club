#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int mod = 1e9 + 7;

vector<int> Mu;
void muSieve(int n){
	Mu.resize(n + 1, -1);
	Mu[0] = 0, Mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(Mu[i]){
			for(int j = 2*i; j <= n; j += i){
				Mu[j] -= Mu[i];
			}
		}
	}
}

const int M = 1e6 + 10;

vector<int> u;
map<int, int> U;

int functionU(int n){
	if(n <= M) return u[n];
	if(U.count(n)) return U[n];
	int ans = 1;
	int m = sqrt(n), l = n / m;
	for(int i = 2; i <= l; ++i){
		ans -= functionU(n / i);
		while(ans >= mod) ans -= mod; while(ans < 0) ans += mod;
	}
	for(int i = 1; i < m; ++i){
		ans -= (lli)(n / i - n / (i + 1)) * functionU(i) % mod;
		while(ans >= mod) ans -= mod; while(ans < 0) ans += mod;
	}
	return U[n] = ans;
}

int h(int n){
	return (lli)(n - 1) * (n - 2) % mod;
}

int inv(int a, int m){
	int r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < m) s0 += m;
	return s0;
}

const int inv_3 = inv(3, mod);

int H(int n){
	return (lli)n * (n - 1) % mod * (n - 2) % mod * inv_3 % mod;
}

int S(int n){
	int ans = 0;
	int m = sqrt(n), l = n / m;
	for(int i = 1; i <= l; ++i){
		ans += (lli)h(i) * functionU(n / i) % mod;
		while(ans >= mod) ans -= mod; while(ans < 0) ans += mod;
	}
	for(int i = 1; i < m; ++i){
		ans += (lli)(H(n / i) - H(n / (i + 1))) * functionU(i) % mod;
		while(ans >= mod) ans -= mod; while(ans < 0) ans += mod;
	}
	return ans;
}

int main(){
	//ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	muSieve(M + 1); u.assign(M + 1, 0);
	for(int i = 1; i <= M; ++i){
		u[i] = u[i - 1] + Mu[i];
		while(u[i] >= mod) u[i] -= mod; while(u[i] < 0) u[i] += mod;
	}
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		cout << S(n) << "\n";
	}
	return 0;
}