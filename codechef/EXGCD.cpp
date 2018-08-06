#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli mod = 1e9 + 7;

vector<int> Phi;
void phiSieve(int n){
	Phi.resize(n + 1);
	for(int i = 1; i <= n; i++) Phi[i] = i;
	for(int i = 2; i <= n; i ++){
		if(Phi[i] == i){
			for(int j = i; j <= n; j += i){
				Phi[j] -= Phi[j] / i;
			}
		}
	}
}

lli inv(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < m) s0 += m;
	return s0;
}
 
int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	phiSieve(2e5 + 10);
	int t, s;
	cin >> t;
	while(t--){
		cin >> s;
		vector<int> a(s), b(s);
		lli den = 1;
		for(int i = 0; i < s; ++i){
			cin >> a[i] >> b[i];
			den *= (b[i] - a[i] + 1);
			den %= mod;
		}
		int M = *max_element(b.begin(), b.end());
		lli num = 0;
		for(int k = 1; k <= M; ++k){
			lli term = Phi[k];
			for(int l = 0; l < s; ++l){
				term *= (b[l] / k - (a[l] - 1) / k);
				term %= mod;
			}
			num = (num + term) % mod;
		}
		lli ans = -num * inv(den, mod) % mod;
		if(ans < 0) ans += mod;
		cout << ans << "\n";
	}
	return 0;
}