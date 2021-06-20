#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e8;

auto divsSieve(int n){
	vector<int> primes, divs(n+1), cnt(n+1), acum(n+1);
	vector<bool> is(n+1, true);
	divs[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(is[i]){
			primes.push_back(i);
			divs[i] = 2;
			cnt[i] = 1;
			acum[i] = i;
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0){
				divs[d] = divs[i / acum[i]] * (cnt[i] + 2);
				cnt[d] = cnt[i] + 1;
				acum[d] = acum[i] * p;
				break;
			}else{
				divs[d] = divs[i] * 2;
				cnt[d] = 1;
				acum[d] = p;
			}
		}
	}
	return divs;
}

const lli N = 1e12;
const int L = pow(N, 2.0/3.0);

const auto divs = divsSieve(L);
vector<lli> g_small(L+1);

lli g(lli n){
	if(n <= L) return g_small[n];
	lli ans = 0;
	lli m = sqrtl(n);
	for(lli k = 1; k <= m; ++k){
		ans += n/k;
	}
	return 2*ans - m*m;
}

lli G(lli n){
	lli ans = 0;
	lli k = 1;
	while(k <= n-1){
		lli a = n/k, b = n/(k+1);
		lli u = min(n/a, n/b-1);
		ans += (a % mod) * (b % mod) * ((u - (k-1)) % mod) % mod;
		if(ans >= mod) ans -= mod;
		k = u+1;
	}
	k = 2;
	while(k <= n){
		lli a = n/k, u = n/a;
		ans -= (g(a) % mod) * ((u - (k-1)) % mod) % mod;
		if(ans < 0) ans += mod;
		k = u+1;
	}
	return ans;
}

int main(){
	for(int i = 1; i <= L; ++i){
		g_small[i] = g_small[i-1] + divs[i];
	}
	lli ans = G(N);
	cout << ans << "\n";
	return 0;
}