#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli N = 1e14;

template<typename T>
struct SumPrimePi{
	int v;
	lli n;
	vector<T> lo, hi;
	vector<int> primes;

	SumPrimePi(lli n): n(n), v(sqrt(n)){
		lo.resize(v+2), hi.resize(v+2);
	}

	void build(){
		lli p, q, j, end, i, d;
		T temp;
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
					hi[i] -= hi[d] - temp;
				else
					hi[i] -= lo[n/d] - temp;
			}
			for(i = v; i >= q; i--){
				lo[i] -= lo[i/p] - temp;
			}
		}
	}

	T get(lli i){
		if(i <= v) return lo[i];
		else return hi[n/i];
	}
};

template<typename T>
struct MultiplicativeSum{
	int v;
	lli n;
	vector<T> lo, hi, smallFP;
	vector<int> primes;

	MultiplicativeSum(lli n, const vector<int> & primes): n(n), v(sqrt(n)), primes(primes){
		lo.resize(v+2), hi.resize(v+2), smallFP.resize(v+2);
	}

	void add(T coef, const SumPrimePi<T> & pi){
		assert(pi.n == n);
		for(int i = 1; i <= v; ++i){
			smallFP[i] += coef * pi.lo[i];
			hi[i] += coef * (pi.hi[i] - pi.lo[v]);
		}
	}

	T getAdded(lli i, lli p){
		if(i <= v){
			return lo[i] + smallFP[max(i, p)] - smallFP[p];
		}else{
			return hi[n/i] + smallFP[v] - smallFP[p];
		}
	}

	void build(function<T(lli, int)> g){
		for(int i = 1; i <= v; ++i){
			lo[i] += T(1);
			hi[i] += T(1);
		}
		for(int r = (int)primes.size()-1; r >= 0; --r){
			lli p = primes[r];
			vector<lli> p_power(1, 1);
			vector<T> gs(1, T(1));
			lli p_pow = p;
			for(int e = 1; ; ++e){
				p_power.push_back(p_pow);
				gs.push_back(g(p, e));
				if(p_pow > n/p) break;
				p_pow *= p;
			}
			for(int i = 1; i <= v; ++i){
				lli next = n / i;
				if(next < p*p) break;
				for(int e = 1; e < p_power.size() && p_power[e] <= next; ++e){
					hi[i] += gs[e] * getAdded(next / p_power[e], p);
				}
				hi[i] -= gs[1];
			}
			for(int i = v; i >= 1; --i){
				if(i < p*p) break;
				for(int e = 1; e <= p_power.size() && p_power[e] <= i; ++e){
					lo[i] += gs[e] * getAdded(i / p_power[e], p);
				}
				lo[i] -= gs[1];
			}
		}
		for(int i = 1; i <= v; ++i){
			lo[i] += smallFP[i];
			hi[i] += smallFP[v];
		}
	}

	lli get(lli i){
		if(i <= v) return lo[i];
		else return hi[n/i];
	}
};

int main(){
	SumPrimePi<lli> sum(N);
	sum.build();
	MultiplicativeSum<lli> ms(N, sum.primes);
	ms.add(2, sum);
	ms.build([](lli p, int e){
		return 1ll << e;
	});
	cout << ms.get(N) << "\n";
	return 0;
}