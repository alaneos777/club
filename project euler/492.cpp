#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

__int128_t powerMod(__int128_t a, __int128_t b, __int128_t m){
	__int128_t ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

lli rec(const vector<lli> & P, const vector<lli> & init, lli n, lli mod){
	int deg = P.size();
	vector<lli> ans(deg), R(2*deg);
	ans[0] = 1;
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	do{
		int d = (n & p) != 0;
		fill(R.begin(), R.end(), 0);
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++)
				(R[i + j + d] += ans[i] * ans[j]) %= mod;
		for(int i = deg-1; i >= 0; i--)
			for(int j = 0; j < deg; j++)
				(R[i + j] += R[i + deg] * P[j]) %= mod;
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);
	lli nValue = 0;
	for(int i = 0; i < deg; i++)
		(nValue += ans[i] * init[i]) %= mod;
	return nValue;
}

bool isPrime(__int128_t n){
	if(n < 2) return false;
	if(!(n & 1)) return n == 2;
	lli d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
		if(n == a) return true;
		lli m = powerMod(a, d, n);
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

const lli N = 1e15;
const lli L = 1e9;
const lli R = L + 1e7;

int main(){
	lli ans = 0;
	for(lli p = L; p <= R; ++p){
		if(!isPrime(p)) continue;
		lli term = (rec({-1 + p, 11}, {2, 11}, powerMod(2, N-1, p*p-1), p) - 5) * powerMod(6, p-2, p) % p;
		if(term < 0) term += p;
		ans += term;
	}
	cout << ans << "\n";
	return 0;
}