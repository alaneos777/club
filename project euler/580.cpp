#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i%p == 0) break;
		}
	}
	return primes;
}

const lli N = lli(1e16) - 1;
const auto primes = sieve(sqrtl(N));

lli F(lli n, int idx = 0){
	lli ans = (n+1)/2;
	for(int i = idx; i < primes.size(); ++i){
		lli p = primes[i];
		lli curr = n / (p*p);
		if(curr == 0) break;
		if(p != 2) ans -= F(curr, i+1);
	}
	return ans;
}

template<typename T>
struct SumPrimePiModulo4{
	int v;
	lli n;
	vector<T> lo, hi;
	vector<T> lo1, hi1;
	vector<int> primes;

	SumPrimePiModulo4(lli n): n(n), v(sqrtl(n)){
		lo.resize(v+2), hi.resize(v+2);
		lo1.resize(v+2), hi1.resize(v+2);
	}

	void build(){
		lli p, q, j, end, i, d;
		T temp, temp1;
		for(p = 1; p <= v; p++){
			lo[p] = p - 1;
			hi[p] = n/p - 1;
			lo1[p] = (p + 3) / 4 - 1;
			hi1[p] = (n/p + 3) / 4 - 1;
		}
		for(p = 2; p <= v; p++){
			if(lo[p] == lo[p-1]) continue;
			primes.push_back(p);
			temp = lo[p-1];
			temp1 = lo1[p-1];
			q = p * p;
			end = (v <= n/q) ? v : n/q;
			for(i = 1; i <= end; ++i){
				d = i * p;
				if(d <= v){
					hi[i] -= (hi[d] - temp);
					if(p % 4 == 1)
						hi1[i] -= (hi1[d] - temp1);
					else if(p % 4 == 3)
						hi1[i] -= (hi[d] - hi1[d]) - (temp - temp1);
				}else{
					hi[i] -= (lo[n/d] - temp);
					if(p % 4 == 1)
						hi1[i] -= (lo1[n/d] - temp1);
					else if(p % 4 == 3)
						hi1[i] -= (lo[n/d] - lo1[n/d]) - (temp - temp1);
				}
			}
			for(i = v; i >= q; i--){
				lo[i] -= (lo[i/p] - temp);
				if(p % 4 == 1)
					lo1[i] -= (lo1[i/p] - temp1);
				else if(p % 4 == 3)
					lo1[i] -= (lo[i/p] - lo1[i/p]) - (temp - temp1);
			}
		}
	}

	T get(lli i) const{
		T s = 0, a = 0;
		if(i <= v){
			s = lo[i];
			a = lo1[i];
		}else{
			s = hi[n/i];
			a = hi1[n/i];
		}
		if(i >= 2) s--;
		return 2*a - s;
	}
};

inline lli g(lli p, int a){
	if(p == 2) return 0;
	if((p&3) == 1) return int(a==1);
	return -int(a==1);
};

lli G(const SumPrimePiModulo4<lli>& pi, lli n, int idx = 0){
	int lo = idx ? pi.primes[idx-1] : 0;
	lli ans = pi.get(n) - pi.get(lo);
	if(idx == 0) ans++;
	for(int i = idx; i < pi.primes.size(); ++i){
		lli p = pi.primes[i];
		if(p * p > n) break;
		int e = 1;
		lli curr = n / p;
		while(curr >= p){
			ans += g(p, e) * G(pi, curr, i+1) + g(p, e+1);
			curr /= p;
			++e;
		}
	}
	return ans;
}

int main(){
	clock_t start = clock();
	SumPrimePiModulo4<lli> pi(N);
	pi.build();

	lli ans = F(N) + G(pi, N);
	for(lli p : primes){
		lli n = N / (p*p);
		if(n == 0) break;
		if(p%4 == 3) ans += F(n) + G(pi, n);
	}
	ans /= 2;
	clock_t end = clock();
	cout << ans << "\n";
	cout << double(end - start) / CLOCKS_PER_SEC << "\n";
	return 0;
}