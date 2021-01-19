#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

void fwt(vector<int> & A, int inv){
	int n = A.size();
	for(int k = 1; k < n; k <<= 1)
		for(int i = 0; i < n; i += k << 1)
			for(int j = 0; j < k; ++j){
				int u = A[i + j], v = A[i + j + k];
				int sum = u + v < mod ? u + v : u + v - mod;
				int rest = u - v < 0 ? u - v + mod : u - v;
				if(inv == -1){
					A[i + j + k] = rest ? mod - rest : 0;
				}else{
					A[i + j + k] = sum;
				}
			}
}

auto sieve(int n){
	vector<bool> is(n+1, true);
	is[0] = is[1] = false;
	vector<int> primes;
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return is;
}

const int N = 1e6, K = 999983;

int main(){
	vector<bool> is = sieve(N);
	vector<int> A(N+1);
	for(int i = 1; i <= N; ++i){
		A[i] = is[i];
	}
	A.resize(nearestPowerOfTwo(A.size()));
	fwt(A, 1);
	for(int & x : A){
		x = powerMod(x, K);
	}
	fwt(A, -1);
	int ans = 0;
	for(int i = 1; i <= N; ++i){
		if(is[i]){
			ans += A[i];
		}
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}