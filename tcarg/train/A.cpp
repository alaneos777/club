#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;

struct bs{
	vector<uint64_t> a;
	size_t sz;

	bs(){}
	bs(size_t sz): sz(sz), a((sz + 63) >> 6) {}

	bool operator[](size_t i) const{
		return (a[i >> 6] >> (63-(i & 63))) & 1;
	}

	void set(size_t i){
		a[i >> 6] |= (1ll << (63-(i & 63)));
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
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
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
	if(fopen("rsa.in", "r")){
		freopen("rsa.in", "r", stdin);
		freopen("rsa.out", "w", stdout);
	}
	int t, m;
	cin >> t >> m;
	auto primes = sieve(2*t*log(t) + 10);
	primes.resize(t);
	vector<bs> A(t, bs(m));
	for(int i = 0; i < m; ++i){
		int bi;
		cin >> bi;
		for(int j = 0; j < t; ++j){
			int p = primes[j], a = 0;
			while(bi % p == 0){
				bi /= p;
				a++;
			}
			if(a&1){
				A[j].set(i);
			}
		}
	}
	int rank = gauss(A);
	int nullity = m - rank;
	cout << (lli(1) << nullity)-1 << "\n";
	return 0;
}