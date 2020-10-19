#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

struct bs{
	vector<uint64_t> a;
	size_t sz;

	bs(){}
	bs(size_t sz): sz(sz), a((sz + 63) >> 6) {}

	bool operator[](size_t i) const{
		return (a[i >> 6] >> (i & 63)) & 1;
	}

	void set(size_t i){
		a[i >> 6] |= (1ll << (i & 63));
	}

	bs& operator^=(const bs& rhs){
		for(size_t i = 0; i < a.size(); ++i){
			a[i] ^= rhs.a[i];
		}
		return *this;
	}
};

auto lpSieve(int n){
	vector<int> primes, lp(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
		}
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
		}
	}
	return lp;
}

auto phiSieve(int n){
	vector<int> phi(n+1);
	iota(phi.begin(), phi.end(), 0);
	for(int i = 2; i <= n; ++i){
		if(phi[i] == i){
			for(int j = i; j <= n; j += i){
				phi[j] -= phi[j] / i;
			}
		}
	}
	return phi;
}

const int N = 1e7;
const auto phi = phiSieve(N+100);
lli two[N+100 + 1];
const lli three_fourths = 3ll * ((mod + 1) / 4) % mod;
const auto lp = lpSieve(N);

auto divs(int n){
	vector<pair<int, int>> f;
	while(n > 1){
		int p = lp[n], e = 0;
		while(n % p == 0){
			n /= p;
			e++;
		}
		f.emplace_back(p, e);
	}
	vector<int> divs;
	function<void(int, int)> dfs = [&](int pos, int acum){
		if(pos == f.size()){
			divs.push_back(acum);
		}else{
			int p_pow = 1;
			int p, e;
			tie(p, e) = f[pos];
			for(int i = 0; i <= e; ++i){
				dfs(pos + 1, acum * p_pow);
				p_pow *= p;
			}
		}
	};
	dfs(0, 1);
	sort(divs.begin(), divs.end());
	return divs;
}

int dim(vector<bs> & A){
	int n = A.size(), i = 0, j = 0;
	while(i < n && j < n){
		if(A[i][j] == 0){
			for(int k = i + 1; k < n; k++){
				if(A[k][j] != 0){
					swap(A[i], A[k]);
					break;
				}
			}
		}
		if(A[i][j] != 0){
			for(int k = i + 1; k < n; k++){
				if(A[k][j] != 0){
					A[k] ^= A[i];
				}
			}
			i++;
		}
		j++;
	}
	return i;
}

lli f(int k){
	vector<bs> A(N, bs(N));
	for(int i = 0; i < N; ++i){
		for(int j = i; j < i+k; ++j){
			A[i].set(j % N);
		}
	}
	return dim(A);
}

lli sum_f(int n){
	lli ans = 0;
	for(int d : divs(n)){
		if(d == 1) ans += 2;
		else ans += (d % 2 == 0 ? 1ll : three_fourths) * phi[d] % mod * two[n+1 - n/d] % mod;
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

lli S(int n){
	lli ans = 0;
	for(int i = 1; i <= n; ++i){
		ans += sum_f(i);
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

int main(){
	two[0] = 1;
	for(int i = 1; i <= N+100; ++i){
		two[i] = two[i-1] * 2ll % mod;
	}
	cout << S(N) << "\n";
	return 0;
}