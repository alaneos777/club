#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli N = 1e12;

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

const auto primes = sieve(sqrtl(N));

__int128_t powerMod(__int128_t a, __int128_t b, __int128_t m){
	__int128_t ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

bool isPrime(lli n){
	if(n < 2) return false;
	if(!(n & 1)) return n == 2;
	lli d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
		if(n == a) return true;
		__int128_t m = powerMod(a, d, n);
		if(m == 1 || m == n - 1) continue;
		int k = 0;
		for(; k < s; ++k){
			m = m * m % n;
			if(m == n - 1) break;
		}
		if(k == s) return false;
	}
	return true;
}

bool proof(lli n){
	lli x = n;
	lli ten = 1;
	while(n){
		lli d = n%10;
		n /= 10;
		lli y = x - d*ten;
		for(lli i = 0; i <= 9; ++i){
			if(isPrime(y + i*ten)){
				return false;
			}
		}
		ten *= 10;
	}
	return true;
}

int main(){
	vector<lli> st;
	for(lli p : primes){
		if(p*p > N) break;
		for(lli q : primes){
			if(p == q) continue;
			if(__int128_t(p)*p * q*q*q > N) break;
			lli x = p*p * q*q*q;
			string str = to_string(x);
			if(str.find("200") != string::npos && proof(x)){
				st.push_back(x);
			}
		}
	}
	sort(st.begin(), st.end());
	cout << st[199] << "\n";
	return 0;
}