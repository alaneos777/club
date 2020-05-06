#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9 + 7;
const lli N = 1e14;

auto muSieve(int n){
	vector<int> Mu(n+1, -1);
	Mu[0] = 0, Mu[1] = 1;
	for(int i = 2; i <= n; ++i)
		if(Mu[i])
			for(int j = 2*i; j <= n; j += i)
				Mu[j] -= Mu[i];
	return Mu;
}

const auto mu = muSieve((int)sqrt(N));

lli gauss(lli n){
	n %= mod;
	return n * (n + 1) % mod * ((mod+1)/2) % mod;
}

lli h(lli n){
	lli ans = 0;
	lli i = 1;
	while(i <= n){
		lli ni = n / i;
		lli u = n / ni;
		ans += (gauss(u) - gauss(i-1)) * (ni%mod) % mod;
		if(ans >= mod) ans -= mod;
		if(ans < 0) ans += mod;
		i = u + 1;
	}
	return ans;
}

int main(){
	lli ans = 0;
	for(lli d = 1; d*d <= N; ++d){
		if(mu[d] == 0) continue;
		ans += d * mu[d] * h(N / (d*d)) % mod;
		while(ans >= mod) ans -= mod;
		while(ans < 0) ans += mod;
	}
	ans -= gauss(N);
	if(ans < 0) ans += mod;
	cout << ans << "\n";
	return 0;
}