#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using comp = complex<lli>;

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

const int M = 150;
const auto primes = sieve(M);

int main(){
	vector<int> primes_1;
	for(int p : primes){
		if(p % 4 == 1){
			primes_1.push_back(p);
		}
	}
	vector<int> Sqrt(M+1, -1);
	for(int i = 1; i*i <= M; ++i){
		Sqrt[i*i] = i;
	}
	int sz = primes_1.size();
	vector<comp> basic(sz);
	for(int i = 0; i < primes_1.size(); ++i){
		for(int a = 1; ; ++a){
			int b2 = primes_1[i] - a*a;
			if(Sqrt[b2] != -1){
				int b = Sqrt[b2];
				basic[i] = {a, b};
				break;
			}
		}
	}

	lli sum = 0;
	vector<int> pos(sz);
	for(int m = 1; m < (1 << sz); ++m){
		int sz2 = 0;
		for(int i = 0; i < sz; ++i){
			if(m & (1 << i)){
				pos[sz2++] = i;
			}
		}
		sz2--;
		for(int s = 0; s < (1 << sz2); ++s){
			comp sol = basic[pos[sz2]];
			for(int i = 0; i < sz2; ++i){
				if(s & (1 << i)){
					sol *= basic[pos[i]];
				}else{
					sol *= conj(basic[pos[i]]);
				}
			}
			sum += min(abs(sol.real()), abs(sol.imag()));
		}
	}
	cout << sum << "\n";
	return 0;
}