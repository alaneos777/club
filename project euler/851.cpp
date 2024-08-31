#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int gauss(vector<vector<lli>>& A){
	int m = A.size(), n = A[0].size(), i = 0, j = 0;
	while(i < m && j < n){
		if(A[i][j] == 0){
			for(int k = i + 1; k < m; k++){
				if(A[k][j] != 0){
					swap(A[i], A[k]);
					break;
				}
			}
		}
		if(A[i][j] != 0){
			lli inv_mult = power(A[i][j], mod - 2);
			if(A[i][j] != 1){
				for(int l = 0; l < n; ++l){
					A[i][l] = A[i][l] * inv_mult % mod;
				}
			}
			for(int k = 0; k < m; k++){
				if(k != i && A[k][j] != 0){
					lli inv_adit = (mod - A[k][j]) % mod;
					for(int l = 0; l < n; ++l){
						A[k][l] += inv_adit * A[i][l] % mod;
						if(A[k][l] >= mod) A[k][l] -= mod;
					}
				}
			}
			i++;
		}
		j++;
	}
	return i;
}

vector<lli> operator*(const vector<lli>& a, const vector<lli>& b){
	if(a.empty() || b.empty()) return {};
	vector<lli> c(a.size() + b.size() - 1);
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			c[i+j] += a[i]*b[j] % mod;
			if(c[i+j] >= mod) c[i+j] -= mod;
		}
	}
	return c;
}

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

const int n = 6;
const int N = 10000;
const int max_p = 2*n-1, deg = n, eqns = (max_p+1)*deg, vars = (max_p+1)*deg;
vector<lli> tau(max(eqns, N)+1);
const auto primes = sieve(N);

int potInFactorial(int n, int p){
	int ans = 0;
	while(n /= p) ans += n;
	return ans;
}

lli divsSumFact(int n, int r){
	lli ans = 1;
	for(int p : primes){
		if(p > n) break;
		int a = potInFactorial(n, p);
		lli pr = power(p, r);
		ans = ans * (power(pr, a+1) - 1) % mod * power(pr - 1, mod-2) % mod;
	}
	return ans;
}

lli tauFact(int n){
	lli ans = 1;
	for(int p : primes){
		if(p > n) break;
		int a = potInFactorial(n, p);
		lli t1 = tau[p], t2 = tau[p] * tau[p] % mod - power(p, 11);
		if(t2 < 0) t2 += mod;
		for(int i = 1; i < a; ++i){
			tie(t1, t2) = make_pair(t2, (tau[p] * t2 - power(p, 11) * t1) % mod);
			if(t2 < 0) t2 += mod;
		}
		ans = ans * t1 % mod;
	}
	return ans;
}

int main(){
	vector<vector<lli>> d(max_p+1, vector<lli>(max(eqns, N)+1));
	for(int i = 1; i <= max(eqns, N); ++i){
		for(int j = i; j <= max(eqns, N); j += i){
			for(int p = 1; p <= max_p; ++p){
				d[p][j] += power(i, p);
				if(d[p][j] >= mod) d[p][j] -= mod;
			}
		}
	}

	vector<lli> rhs = {1};
	for(int i = 1; i <= n; ++i){
		rhs = rhs * d[1];
	}
	rhs.resize(eqns+1);

	for(int i = 1; i <= max(eqns, N); ++i){
		tau[i] = (lli)i * i % mod * i % mod * i % mod * d[1][i] % mod;
		for(int j = 1; j < i; ++j){
			lli term = (35ll * j % mod * j % mod - 52ll * j % mod * i % mod + 18ll * i % mod * i % mod) % mod;
			if(term < 0) term += mod;
			tau[i] -= 24ll * j % mod * j % mod * term % mod * d[1][j] % mod * d[1][i-j] % mod;
			if(tau[i] < 0) tau[i] += mod;
		}
	}
	d[0] = tau;
	d[0].resize(eqns+1);

	vector<vector<lli>> A(eqns, vector<lli>(vars+1));
	for(int i = 1; i <= eqns; ++i){
		for(int p = 0; p <= max_p; ++p){
			for(int j = 0; j < deg; ++j){
				A[i-1][deg*p+j] = power(i, j) * d[p][i] % mod;
			}
		}
	}
	for(int i = 1; i <= eqns; ++i){
		A[i-1][vars] = rhs[i];
	}

	int rank_augmented = gauss(A), rank = 0;
	vector<int> pivot(eqns);
	for(int i = 0; i < eqns; ++i){
		for(int j = 0; j < vars; ++j){
			if(A[i][j] != 0){
				pivot[i] = j;
				rank++;
				break;
			}
		}
	}
	pivot.resize(rank);

	if(rank < rank_augmented){
		cout << "-1\n";
		return 0;
	}

	vector<lli> coef(vars);
	for(int i = 0; i < rank; ++i){
		coef[pivot[i]] = A[i][vars];
	}

	lli Nfact = 1;
	for(lli i = 1; i <= N; ++i){
		Nfact = Nfact * i % mod;
	}

	lli ans = 0;
	for(int p = 0; p <= max_p; ++p){
		lli c = (p == 0 ? tauFact(N) : divsSumFact(N, p));
		for(int j = 0; j < deg; ++j){
			ans += coef[deg*p+j] * power(Nfact, j) % mod * c % mod;
			if(ans >= mod) ans -= mod;
		}
	}
	ans = ans * power(2, n) % mod;

	cout << ans << "\n";

	return 0;
}