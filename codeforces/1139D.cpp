#include <iostream>
#include <vector>
using namespace std;
using lli = long long int;
const lli mod =1e9 + 7;

vector<int> Mu;
void sieve(int n){
	Mu.resize(n + 1, -1);
	Mu[0] = 0, Mu[1] = 1;
	for(int i = 2; i <= n; ++i)
		if(Mu[i])
			for(int j = 2*i; j <= n; j += i)
				Mu[j] -= Mu[i];
}

lli inverse(lli a){
	lli r0 = a, r1 = mod, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(r0 == -1) s0 = -s0;
	if(s0 < 0) s0 += mod;
	return s0;
}

int main(){
	sieve(1e5);
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli m;
	cin >> m;
	lli inv_m = inverse(m);
	lli ans = inv_m;
	for(int k = 2; k <= m; ++k){
		lli r = (m / k) * inv_m % mod;
		ans += Mu[k] * r * (r - 2) % mod * inverse(1-r) % mod;
		while(ans >= mod) ans -= mod;
		while(ans < 0) ans += mod;
	}
	cout << ans << "\n";
	return 0;
}