#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli M = 1e12;

lli isPrime(lli n){
	if(n == 1) return false;
	for(lli p = 2; p*p <= n; ++p){
		if(n % p == 0) return false;
	}
	return true;
}

int main(){
	vector<vector<lli>> H(3);
	for(lli a = 1; a <= M; a *= 2){
		H[0].push_back(a);
	}
	for(lli b = 1; b <= M; b *= 3){
		H[1].push_back(b);
	}
	for(lli c = 1; c <= M; c *= 5){
		H[2].push_back(c);
	}
	for(lli a = 1; a <= M; a *= 2){
		for(lli b = a; b <= M; b *= 3){
			for(lli c = b; c <= M; c *= 5){
				if(c + 1 >= 7 && isPrime(c + 1)){
					H.push_back({c + 1});
				}
			}
		}
	}
	set<lli> ans = {1};
	for(const vector<lli> & arr : H){
		vector<lli> nuevo;
		for(lli x : arr){
			for(lli y : ans){
				__int128 next = (__int128)x * y;
				if(next > M) break;
				nuevo.push_back(next);
			}
		}
		for(lli y : nuevo){
			ans.insert(y);
		}
	}
	uint64_t sum = 0;
	for(lli x : ans){
		sum += x;
	}
	uint32_t s = sum;
	cout << s << "\n";
	return 0;
}