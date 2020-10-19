#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int mod = 1e9;

struct SumPrimePi{
	int v, k;
	lli n;
	vector<int> lo, hi;
	vector<int> primes;

	SumPrimePi(lli n): n(n), v(sqrt(n)){
		lo.resize(v+2), hi.resize(v+2);
	}

	int Sum(lli n){
		if(n & 1) return ((n+1)/2 % mod) * (n % mod) % mod;
		else return (n/2 % mod) * ((n+1) % mod) % mod;
	}

	void build(){
		lli p, q, j, end, i, d;
		int temp;
		for(p = 1; p <= v; p++){
			lo[p] = Sum(p) - 1;
			hi[p] = Sum(n/p) - 1;
			if(lo[p] < 0) lo[p] += mod;
			if(hi[p] < 0) hi[p] += mod;
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
					hi[i] -= (hi[d] - temp) * p % mod;
				else
					hi[i] -= (lo[n/d] - temp) * p % mod;
				while(hi[i] >= mod) hi[i] -= mod;
				while(hi[i] < 0) hi[i] += mod;
			}
			for(i = v; i >= q; i--){
				lo[i] -= (lo[i/p] - temp) * p % mod;
				while(lo[i] >= mod) lo[i] -= mod;
				while(lo[i] < 0) lo[i] += mod;
			}
		}
	}

	int get(lli i) const{
		if(i <= v) return lo[i];
		else return hi[n/i];
	}
};

const lli N = 201820182018ll;

int f(lli n, int idx, const SumPrimePi & pi){
	lli ans = pi.get(n) - pi.get(pi.primes[idx] - 1);
	if(ans < 0) ans += mod;
	for(int i = idx; i < pi.primes.size(); ++i){
		lli p = pi.primes[i];
		if(p*p > n) break;
		ans += f(n / p, i, pi);
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

int main(){
	SumPrimePi pi(N);
	pi.build();
	cout << f(N, 0, pi) << "\n";
	return 0;
}