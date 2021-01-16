#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
const lli mod = 1e9 + 7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

struct bs{
	vector<uint64_t> a;
	size_t sz;

	bs(){}
	bs(size_t sz): sz(sz), a((sz + 63) >> 6) {}

	bool operator[](size_t i) const{
		return (a[i >> 6] >> (63-(i & 63))) & 1;
	}

	bool operator>(const bs& rhs) const{
		return a > rhs.a;
	}

	void flip(size_t i){
		a[i >> 6] ^= (1ll << (63-(i & 63)));
	}

	bs& operator^=(const bs& rhs){
		for(size_t i = 0; i < a.size(); ++i){
			a[i] ^= rhs.a[i];
		}
		return *this;
	}
};

int gauss(vector<bs> & A){
	int m = A.size(), n = A[0].sz, i = 0, j = 0;
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
			for(int k = 0; k < m; k++){
				if(k != i && A[k][j] != 0){
					A[k] ^= A[i];
				}
			}
			i++;
		}
		j++;
	}
	return i;
}

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const auto primes = sieve(70);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for(int & ai : a){
		cin >> ai;
	}
	int m = primes.size();
	vector<bs> A(m, bs(n));
	for(int i = 0; i < m; ++i){
		int p = primes[i];
		for(int j = 0; j < n; ++j){
			int e = 0;
			while(a[j] % p == 0){
				e++;
				a[j] /= p; 
			}
			if(e & 1) A[i].flip(j);
		}
	}
	int rank = gauss(A);
	int ans = power(2, n-rank) - 1;
	cout << ans << "\n";
	return 0;
}