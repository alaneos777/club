#include <bits/stdc++.h>
using namespace std;
using uint = uint32_t;

const uint N = 2e9;
/*auto lpSieve(uint n){
	vector<uint> primes, lp(n+1);
	for(uint i = 2; i <= n; ++i){
		if(lp[i] == 0){
			lp[i] = i;
			primes.push_back(i);
		}
		for(uint p : primes){
			uint d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
		}
	}
	return lp;
}

const auto lp = lpSieve(N);

bool check(uint n){
	bool test = true;
	bool has1 = false, has2 = false, has3 = false, has7 = false;
	while(n > 1){
		uint p = lp[n], a = 0;
		while(n % p == 0){
			n /= p;
			a++;
		}
		if(p == 2){
			// a^2 + b^2
			has1 |= (a%2 == 1);
			// a^2 + 3b^2
			has3 |= (a > 0);
			test &= (a%2 == 0);
			// a^2 + 7b^2
			has7 |= (a >= 3);
		}else{
			uint p4 = p%4, p8 = p%8, p6 = p%6, p14 = p%14;
			// a^2 + b^2
			if(p4 == 3){
				test &= (a%2 == 0);
			}else if(p4 == 1){
				has1 = true;
			}
			// a^2 + 2b^2
			if(p8 == 5 || p8 == 7){
				test &= (a%2 == 0);
			}else if(p8 == 1 || p8 == 3){
				has2 = true;
			}
			// a^2 + 3b^2
			if(p6 == 5){
				test &= (a%2 == 0);
			}else if(p6 == 1){
				has3 = true;
			}
			// a^2 + 7b^2
			if(p14 == 3 || p14 == 5 || p14 == 13){
				test &= (a%2 == 0);
			}else if(p14 == 1 || p14 == 9 || p14 == 11){
				has7 = true;
			}
		}
	}
	test &= has1;
	test &= has2;
	test &= has3;
	test &= has7;
	return test;
}*/

int main(){
	/*uint ans = 0;
	int cnt = 0;
	for(uint n = 1; n <= N; ++n){
		ans += check(n);
	}
	cout << ans << "\n";*/
	vector<uint8_t> cnt((N+1)/2);
	vector<uint> k = {1, 2, 3, 7};
	for(uint i = 0; i < k.size(); ++i){
		for(uint a = 1; a*a <= N; ++a){
			for(uint b = 1; a*a + k[i]*b*b <= N; ++b){
				uint n = a*a + k[i]*b*b;
				if(n&1) cnt[n>>1] |= 1<<(i+4);
				else cnt[n>>1] |= 1<<i;
			}
		}
	}
	uint ans = 0;
	for(uint n = 1; n <= N; ++n){
		int val = (n&1 ? cnt[n>>1]>>4 : cnt[n>>1]&15);
		if(val == 15) ans++;
	}
	cout << ans << "\n";
	return 0;
}