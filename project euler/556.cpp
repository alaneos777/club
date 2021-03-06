#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

template<typename T>
struct SumPrimePiModulo4{
	int v;
	lli n;
	vector<T> lo, hi;
	vector<T> lo1, hi1;
	vector<int> primes;

	SumPrimePiModulo4(lli n): n(n), v(sqrt(n)){
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
		T ans = 0;
		if(i <= v) return (2 <= i) + 2*lo1[i];
		else return (2 <= i) + 2*hi1[n/i];
	}
};

template<typename T>
inline T g(lli p, int a){
	int rem = p & 3;
	if(rem == 2){
		return a == 1;
	}else if(rem == 1){
		if(a == 1) return 2;
		else if(a == 2) return 1;
		else return 0;
	}else{
		return a == 2;
	}
}

template<typename T>
T f(const SumPrimePiModulo4<T> & pi, lli n, int idx = 0){
	T ans = pi.get(n) - pi.get(pi.primes[idx] - 1);
	if(idx == 0) ans++;
	for(int i = idx; i < pi.primes.size(); ++i){
		lli p = pi.primes[i];
		if(p * p > n) break;
		int e = 1;
		lli curr = n / p;
		while(curr >= p){
			T tmp = g<T>(p, e);
			if(tmp) ans += tmp * f(pi, curr, i+1);
			ans += g<T>(p, e+1);
			curr /= p;
			++e;
		}
	}
	return ans;
}

int main(){
	lli n = 1e14;
	SumPrimePiModulo4<lli> pi(n);
	pi.build();
	pi.primes.push_back(pi.v + 1);
	cout << f<lli>(pi, n) << "\n";
	return 0;
}