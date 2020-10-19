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

vector<int> pi, primes;
void sieve(int n){
	vector<bool> is(n+1, true);
	pi.resize(n+1);
	is[0] = is[1] = false;
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	for(int i = 1; i <= n; ++i){
		pi[i] = pi[i-1] + is[i];
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	sieve(1e7);
	lli n;
	while(cin >> n){
		if(n <= 1e7){
			cout << pi[n] << "\n";
		}else{
			SumPrimePi pi(n);
			pi.build();
			cout << pi.get(n) << "\n";
		}
	}
	return 0;
}