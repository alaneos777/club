#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

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

inline lli g2(lli p, int a){
	if(p == 2) return power(p, (a+1)/2);
	else return power(p, a/2);
};

lli SUM2(const SumPrimePi & pi, lli n, int idx = 0){
	int lo = idx ? pi.primes[idx-1] : 0;
	lli ans = pi.get(n) - pi.get(lo);
	if(lo < 2 && 2 <= n) ans++;
	if(idx == 0){
		ans++;
	}
	for(int i = idx; i < pi.primes.size(); ++i){
		lli p = pi.primes[i];
		if(p * p > n) break;
		int e = 1;
		lli curr = n / p;
		while(curr >= p){
			ans += g2(p, e) * SUM2(pi, curr, i+1) + g2(p, e+1);
			curr /= p;
			++e;
		}
	}
	return ans;
}

inline lli g1(lli p, int a){
	if(p == 2) return power(p, a/2);
	else return power(p, (a+1)/2);
};

lli GET(const SumPrimePi & pi, lli l, lli r, lli N){
	if(l > r) return 0;
	lli ans = 0;
	lli i = l;
	while(i <= r){
		lli u = N / (N / i);
		ans += (N/i) * (pi.get(min(u, r)) - pi.get(i - 1));
		i = u + 1;
	}
	return ans;
}

lli SUM1(const SumPrimePi & pi, lli n, lli N, int idx = 0){
	int lo = idx ? pi.primes[idx-1] : 0;
	lli ans = GET(pi, lo+1, n, N);
	if(lo < 2 && 2 <= n){
		ans = ans - N/2 + N;
	}
	if(idx == 0){
		ans += N/1;
	}
	for(int i = idx; i < pi.primes.size(); ++i){
		lli p = pi.primes[i];
		if(p * p > n) break;
		int e = 1;
		lli curr = n / p;
		while(curr >= p){
			ans += SUM1(pi, curr, N/g1(p, e), i+1) + N/g1(p, e+1);
			curr /= p;
			++e;
		}
	}
	return ans;
}

const lli N = 1e12;
auto pi = SumPrimePi(N);

int main(){
	clock_t start = clock();
	pi.build();
	lli ans = N - SUM2(pi, N) + SUM1(pi, N, N);
	cout << ans << "\n";
	cout << fixed << setprecision(3) << double(clock() - start) / CLOCKS_PER_SEC << "s" << "\n";
	return 0;
}