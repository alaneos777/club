#include <bits/stdc++.h>
using namespace std;
using lli = uint64_t;

const lli M = 1e12;

__int128_t powerMod(__int128_t a, __int128_t b, __int128_t m){
	__int128_t ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

bool isPrime(__int128_t n){
	if(n < 2) return false;
	if(!(n & 1)) return n == 2;
	__int128_t d = n - 1, s = 0;
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

int main(){
	vector<lli> H, A;
	for(lli a = 1; a <= M; a *= 2){
		for(lli b = a; b <= M; b *= 3){
			for(lli c = b; c <= M; c *= 5){
				if(c + 1 >= 7 && isPrime(c + 1)){
					H.push_back(c + 1);
				}
				A.push_back(c);
			}
		}
	}
	sort(A.begin(), A.end());

	set<lli> multiples = {1};
	for(lli x : H){
		vector<lli> nuevo;
		for(lli y : multiples){
			__uint128_t next = (__uint128_t)x * y;
			if(next > M) break;
			nuevo.push_back(next);
		}
		for(lli y : nuevo){
			multiples.insert(y);
		}
	}

	vector<lli> acum;
	partial_sum(A.begin(), A.end(), back_inserter(acum));

	lli ans = 0;
	for(lli x : multiples){
		lli upper = M / x;
		int pos = upper_bound(A.begin(), A.end(), upper) - A.begin();
		ans += x * acum[pos-1];
	}
	cout << uint32_t(ans) << "\n";
	return 0;
}