#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli inf = 1e18;

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

const int M = 1e5;
const vector<int> primes = sieve(M);

inline lli p(int t){
	return primes[t];
}

const int k = 7000, n = p(7000);

vector<lli> operator*(const vector<lli>& a, const vector<lli>& b){
	vector<lli> c(k, -inf);
	for(int i = 0; i < k; ++i){
		for(int j = 0; j < k; ++j){
			int idx = i+j;
			if(idx >= k) idx -= k;
			c[idx] = max(c[idx], a[i] + b[j]);
		}
	}
	return c;
}

vector<lli> power(vector<lli> a, lli b){
	vector<lli> ans(k, -inf);
	ans[0] = 0;
	while(b){
		if(b&1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

int main(){
	vector<lli> a(k);
	for(int i = 0; i < k; ++i){
		a[i] = p(i);
	}
	a = power(a, n);
	cout << a[0] << "\n";
	return 0;
}