#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

struct SumPrimePi{
	int v;
	lli n;
	vector<lli> lo, hi;
	vector<int> primes;

	SumPrimePi(lli n): n(n), v(sqrt(n)){
		lo.resize(v+2), hi.resize(v+2);
	}

	void build(){
		lli p, q, j, end, i, d;
		lli temp;
		for(p = 1; p <= v; p++){
			lo[p] = p - 1;
			hi[p] = n/p - 1;
		}
		for(p = 2; p <= v; p++){
			if(lo[p] == lo[p-1]) continue;
			primes.push_back(p);
			temp = lo[p-1];
			q = p * p;
			end = (v <= n/q) ? v : n/q;
			for(i = 1; i <= end; ++i){
				d = i * p;
				if(d <= v)
					hi[i] -= (hi[d] - temp);
				else
					hi[i] -= (lo[n/d] - temp);
			}
			for(i = v; i >= q; i--){
				lo[i] -= (lo[i/p] - temp);
			}
		}
	}

	lli get(lli i) const{
		if(i <= v) return lo[i];
		else return hi[n/i];
	}
};

lli pot(lli n, lli p){
	lli ans = 0;
	while(n /= p) ans += n;
	return ans;
}

uint64_t mult(uint64_t a, uint64_t b, uint64_t m){
	if(a >= m) a %= m;
	if(b >= m) b %= m;
	uint64_t c = (long double)a * b / m;
	int64_t r = (int64_t)(a * b - c * m) % (int64_t)m;
	return r < 0 ? r + m : r;
}

lli power(lli a, lli b, lli m){
	lli ans = 1;
	a %= m;
	while(b){
		if(b & 1) ans = mult(ans, a, m);
		b >>= 1;
		a = mult(a, a, m);
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli n, m;
		cin >> n >> m;
		if(n == 0){
			cout << 1ll%m << "\n";
			continue;
		}
		SumPrimePi pi(n);
		pi.build();
		lli ans = 1;
		for(lli p : pi.primes){
			ans = mult(ans, pot(n, p) + 1, m);
		}
		auto is = [&](lli x){
			for(lli p : pi.primes){
				if(p*p > x) break;
				if(x % p == 0) return false;
			}
			return true;
		};
		for(lli p = pi.v+1; p <= n/pi.v; ++p){
			if(is(p)) ans = mult(ans, pot(n, p) + 1, m);
		}
		for(lli i = 1; i < pi.v; ++i){
			ans = mult(ans, power(i + 1, pi.get(n / i) - pi.get(n / (i + 1)), m), m);
		}
		cout << ans << "\n";
	}
	return 0;
}