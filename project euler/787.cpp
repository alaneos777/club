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

tuple<int, int, int> extgcd(int a, int b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		int q = a/b;
		auto[d, x, y] = extgcd(b, a - b*q);
		return {d, y, x - y*q};
	}
}

bool mem[11111][11111];
bool clc[11111][11111];

bool f(int a, int b){
	if(a == 0 || b == 0) return false;
	bool& ans = mem[a][b];
	bool& calc = clc[a][b];
	if(calc) return ans;
	calc = true;
	auto[g, x, y] = extgcd(a, b);
	assert(g == 1);
	int d = abs(x), c = abs(y);
	ans = !f(a-c, b-d) || !f(c, d);
	return ans;
}

lli method0(int n){
	lli ans = 0;
	for(int a = 1; a <= n; ++a){
		for(int b = 1; a+b <= n; ++b){
			if(__gcd(a, b) == 1){
				ans += f(a, b);
			}
		}
	}
	return ans;
}

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
					hi[i] -= (hi[d] - temp);
				else
					hi[i] -= (lo[n/d] - temp);
			}
			for(i = v; i >= q; i--){
				lo[i] -= (lo[i/p] - temp);
			}
		}
	}

	T get(lli i) const{
		T ans = 0;
		if(i <= v) ans = lo[i];
		else ans = hi[n/i];
		if(i >= 2) ans--;
		return ans;
	}
};

template<typename T>
struct MultiplicativeSum{
	int v;
	lli n;
	vector<T> lo, hi, smallFP;
	vector<int> primes;

	MultiplicativeSum(lli n, const vector<int>& primes): n(n), v(sqrt(n)), primes(primes){
		lo.resize(v+2), hi.resize(v+2), smallFP.resize(v+2);
	}

	void add(T coef, const auto & pi){
		assert(pi.n == n);
		for(int i = 1; i <= v; ++i){
			smallFP[i] += coef * pi.get(i);
			hi[i] += coef * (pi.get(n/i) - pi.get(v));
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
			lo[i] += 1;
			hi[i] += 1;
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

	T get(lli i) const{
		if(i <= v) return lo[i];
		else return hi[n/i];
	}
};

lli method1(lli n){
	SumPrimePi<lli> pi(n);
	pi.build();
	MultiplicativeSum<lli> sum(n, pi.primes);
	sum.add(-1, pi);
	sum.build([&](lli p, int a){
		if(p == 2 || a >= 2) return 0ll;
		return -1ll;
	});
	lli ans = 0;
	lli d = 1;
	while(2*d <= n){
		lli nd = n/d, r = n/nd;
		lli term = (nd + 1) * (nd + 1) / 8;
		ans += term * (sum.get(r) - sum.get(d-1));
		d = r+1;
	}
	ans = 2*ans - 1;
	return ans;
}

auto muSieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	vector<int8_t> mu(n+1);
	mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(is[i]){
			primes.push_back(i);
			mu[i] = -1;
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i%p == 0) break;
			else mu[d] = -mu[i];
		}
	}
	return mu;
}

lli method2(lli n){
	int M = powl(n, 2.0/3.0);
	auto mu = muSieve(M);
	vector<lli> small(M+1);
	map<lli, lli> big;
	for(int i = 1; i <= M; i++){
		if(i&1) small[i] = small[i-1] + mu[i];
		else small[i] = small[i-1];
	}
	function<lli(lli)> U = [&](lli n) -> lli{
		if(n <= M) return small[n];
		if(big.count(n)) return big[n];
		lli ans = 1 + __lg((int64_t)n);
		lli d = 2;
		while(d <= n){
			lli nd = n/d, r = n/nd;
			ans -= U(nd) * (r - (d-1));
			d = r+1;
		}
		return big[n] = ans;
	};
	lli ans = 0;
	lli d = 1;
	while(2*d <= n){
		lli nd = n/d, r = n/nd;
		lli term = (nd + 1) * (nd + 1) / 8;
		ans += term * (U(r) - U(d-1));
		d = r+1;
	}
	ans = 2*ans - 1;
	return ans;
}

const lli N = 1e9;

int main(){
	//cout << method0(N) << "\n";
	cout << method1(N) << "\n";
	cout << method2(N) << "\n";
	return 0;
}