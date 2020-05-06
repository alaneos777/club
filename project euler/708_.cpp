#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

template<typename T>
struct SumPrimePi{
	int v;
	lli n;
	int k;
	vector<T> lo, hi;
	vector<int> primes;

	SumPrimePi(lli n, int k = 0): n(n), v(sqrt(n)), k(k){
		lo.resize(v+2), hi.resize(v+2);
	}

	T power(T a, lli b){
		T ans = 1;
		while(b){
			if(b & 1) ans *= a;
			b >>= 1;
			a *= a;
		}
		return ans;
	}

	T powerSum(T n, int k){
		if(k == 0) return n;
		if(k == 1) return n * (n + 1) / 2;
		return 0;
	}

	void build(){
		lli p, q, j, end, i, d;
		T temp;
		for(p = 1; p <= v; p++){
			lo[p] = powerSum(p, k) - 1;
			hi[p] = powerSum(n/p, k) - 1;
		}
		for(p = 2; p <= v; p++){
			T pk = power(p, k);
			if(lo[p] == lo[p-1]) continue;
			primes.push_back(p);
			temp = lo[p-1];
			q = p * p;
			end = (v <= n/q) ? v : n/q;
			for(i = 1; i <= end; ++i){
				d = i * p;
				if(d <= v)
					hi[i] -= (hi[d] - temp) * pk;
				else
					hi[i] -= (lo[n/d] - temp) * pk;
			}
			for(i = v; i >= q; i--){
				lo[i] -= (lo[i/p] - temp) * pk;
			}
		}
	}

	T get(lli i){
		if(i <= v) return lo[i];
		else return hi[n/i];
	}
};

template<typename T>
T g(lli p, int e){
	return 1ll << e;
}

template<typename T>
T f(SumPrimePi<T> & pi, lli n, int idx = 0){
	//# of primes between primes[idx] and n
	T t = pi.get(n) - pi.get(pi.primes[idx] - 1);
	T ans = t * 2;
	for(int i = idx; i < pi.primes.size(); ++i){
		lli p = pi.primes[i];
		if(p * p > n) break;
		int e = 1;
		lli curr = n / p;
		while(curr >= p){
			ans += g<T>(p, e) * f(pi, curr, i+1) + g<T>(p, e+1);
			curr /= p;
			++e;
		}
	}
	return ans;
}

int main(){
	lli N = 1e14;
	SumPrimePi<lli> pi(N);
	pi.build();
	pi.primes.push_back(pi.v + 1);
	cout << 1 + f<lli>(pi, N) << "\n";
	return 0;
}