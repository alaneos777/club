#include <bits/stdc++.h>
using namespace std;

auto sieve(int n){
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

auto phiSieve(int n){
	vector<int> phi(n+1);
	iota(phi.begin(), phi.end(), 0);
	for(int i = 2; i <= n; ++i){
		if(phi[i] == i){
			for(int j = i; j <= n; j += i){
				phi[j] -= phi[j] / i;
			}
		}
	}
	return phi;
}

const int M = 2e4;
const auto lp = sieve(9*M);
const auto phi = phiSieve(9*M);
 
auto fact(int n){
	vector<pair<int, int>> f;
	while(n > 1){
		int p = lp[n];
		int cnt = 0;
		while(n % p == 0){
			n /= p;
			cnt++;
		}
		f.emplace_back(p, cnt);
	}
	return f;
}

int64_t power(int64_t a, int64_t b, int64_t m){
	int64_t ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans % m;
}

int order(int x, int m){
	int order = phi[m];
	auto f = fact(order);
	for(const auto & par : f){
		int p, a;
		tie(p, a) = par;
		while(a--) order /= p;
		int tmp = power(x, order, m);
		while(tmp != 1){
			tmp = power(tmp, p, m);
			order *= p;
		}
	}
	return order;
}

int main(){
	int64_t sum = 0;
	int cnt = 0;
	for(int n = 2; n <= M; ++n){
		if(lp[n] == n) continue;
		if(__gcd(n, 10) != 1) continue;
		if((n - 1) % order(10, 9*n) == 0){
			sum += n;
			cnt++;
			cout << cnt << ". " << n << "\n";
			if(cnt == 25) break;
		}
	}
	cout << sum << "\n";
	return 0;
}