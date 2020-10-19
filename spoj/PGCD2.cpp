#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;

vector<bool> isPrime;
vector<int> primes;

auto muSieve(int n){
	vector<int8_t> Mu(n+1);
	Mu[0] = 0, Mu[1] = 1;
	isPrime.resize(n+1, true);
	isPrime[0] = isPrime[1] = false;
	for(int i = 2; i <= n; ++i){
		if(isPrime[i]){
			primes.push_back(i);
			Mu[i] = -1;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0){
				break;
			}else{
				Mu[d] = -Mu[i];
			}
		}
	}
	return Mu;
}

template<typename T>
struct SumPrimePi{
	int v;
	int64_t n;
	vector<T> lo, hi;
	vector<int64_t> avaliable;

	SumPrimePi(int64_t n): n(n), v(sqrt(n)){
		lo.resize(v+2), hi.resize(v+2);
	}

	void build(){
		int64_t p, q, j, end, i, d;
		T temp;
		for(p = 1; p <= v; p++){
			lo[p] = p - 1;
			hi[p] = n/p - 1;
			avaliable.push_back(n/p);
		}
		reverse(avaliable.begin(), avaliable.end());
		for(p = 2; p <= v; p++){
			if(lo[p] == lo[p-1]) continue;
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

	T get(int64_t i) const{
		if(i <= v) return lo[i];
		else if(binary_search(avaliable.begin(), avaliable.end(), i)) return hi[n/i];
		else return -1;
	}
};

int T = 0;

vector<int> h, H_small;
map<int64_t, lli> H_big;
lli H(int64_t n, const SumPrimePi<int64_t> & pi_m, const SumPrimePi<int64_t> & pi_n){
	if(n <= T) return H_small[n];
	if(H_big.find(n) != H_big.end()) return H_big[n];
	lli ans = pi_m.get(n);
	if(ans == -1) ans = pi_n.get(n);
	int m = sqrt(n), l = n / m;
	for(int i = 2; i <= l; ++i){
		ans -= H(n/i, pi_m, pi_n);
	}
	for(int i = 1; i < m; ++i){
		ans -= (n/i - n/(i+1)) * H_small[i];
	}
	return H_big[n] = ans;
}

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

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	vector<pair<int64_t, int64_t>> tests;
	int64_t M = 0;
	while(t--){
		int64_t m, n;
		cin >> m >> n;
		tests.emplace_back(m, n);
		M = max(M, max(m, n));
	}

	T = max(3e7, pow(M, 2.0 / 3.0));
	h.resize(T+1), H_small.resize(T+1);
	auto mu = muSieve(T);
	for(int p : primes){
		for(int j = p, r = 1; j <= T; j += p, ++r){
			h[j] += mu[r];
		}
	}
	for(int i = 1; i <= T; ++i){
		H_small[i] = H_small[i-1] + h[i];
	}

	for(const auto & test : tests){
		int64_t m, n;
		tie(m, n) = test;
		lli ans = 0;
		int64_t d = 1;
		int64_t limit = min(m, n);
		SumPrimePi<int64_t> pi_m(m), pi_n(n);
		if(m > T) pi_m.build();
		if(n > T) pi_n.build();
		while(d <= limit){
			int64_t md = m / d, nd = n / d;
			int64_t u = min(m / md, n / nd);
			ans += (H(u, pi_m, pi_n) - H(d-1, pi_m, pi_n)) * md * nd;
			d = u + 1;
		}
		cout << ans << "\n";
	}
	return 0;
}