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
		if(i <= v) return lo[i] + 2*lo1[i];
		else return hi[n/i] + 2*hi1[n/i];
	}
};

template<typename T>
inline T g(lli p, int a){
	if(p == 2 || (p & 3) == 3) return 1;
	return 2*a + 1;
}

template<typename T>
T f(const SumPrimePiModulo4<T> & pi, lli n, int idx = 0){
	// sum of g(p, 1) for primes p such that primes[idx] <= p <= n
	int lo = idx ? pi.primes[idx-1] : 0;
	T ans = pi.get(n) - pi.get(lo);
	if(idx == 0) ans++;
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
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n;
	cin >> n;
	SumPrimePiModulo4<lli> pi(n);
	pi.build();
	cout << (f<lli>(pi, n) - n) / 2 << "\n";
	return 0;
}