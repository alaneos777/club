#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;

ostream &operator<<(ostream &os, const __int128 & value){
	char buffer[64];
	char *pos = end(buffer) - 1;
	*pos = '\0';
	__int128 tmp = value < 0 ? -value : value;
	do{
		--pos;
		*pos = tmp % 10 + '0';
		tmp /= 10;
	}while(tmp != 0);
	if(value < 0){
		--pos;
		*pos = '-';
	}
	return os << pos;
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

template<typename T>
struct SumPrimePi{
	int v, k;
	lli n;
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

	T get(lli i) const{
		if(i <= v) return lo[i];
		else return hi[n/i];
	}
};

const lli M = 12345678;
//const lli M = 1e14;
SumPrimePi<lli> pi_0(M, 0);
SumPrimePi<lli> pi_1(M, 1);
vector<int> primes;

template<typename T>
T SUM(function<T(lli, int)> g, function<T(lli)> G, lli n, int idx = 0){
	int lo = idx ? primes[idx-1] : 0;
	T ans = G(n) - G(lo);
	if(idx == 0) ans++;
	for(int i = idx; i < primes.size(); ++i){
		lli p = primes[i];
		if(p * p > n) break;
		int e = 1;
		lli curr = n / p;
		while(curr >= p){
			ans += g(p, e) * SUM(g, G, curr, i+1) + g(p, e+1);
			curr /= p;
			++e;
		}
	}
	return ans;
}

auto g2 = [&](lli p, int a){
	if(p == 2) return power(2, a) * (power(2, a/2 + 1) + power(2, (a+3)/2) - 3);
	return power(p, a-1) * (power(p, a/2 + 1) + power(p, (a+1)/2) - 1);
};

auto G2 = [&](lli n){
	lli ans = 2*pi_1.get(n) - pi_0.get(n);
	if(n >= 2) ans += 3;
	return ans;
};

lli G(lli n){
	lli m = (n+1)/2;
	return SUM<lli>(g2, G2, n/2) - m*m;
}

int main(){
	pi_0.build();
	pi_1.build();
	primes = pi_0.primes;
	cout << G(M) << "\n";
	return 0;
}