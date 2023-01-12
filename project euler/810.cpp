#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli mult(uint32_t a, uint32_t b){
	lli ans = 0;
	while(b){
		ans ^= a<<__builtin_ctz(b);
		b -= 1<<__builtin_ctz(b);
	}
	return ans;
}

const int M = 2e8;
const int N = 5e6;

int main(){
	vector<bool> is(M+1, true);
	is[0] = is[1] = false;
	vector<int> primes;
	for(int i = 2; i <= M; ++i){
		if(is[i]){
			primes.push_back(i);
			for(int j = i; (lli)i*j <= 3*M; ++j){
				lli pos = mult(i,j);
				if(pos <= M){
					is[pos] = false;
				}
			}
		}
	}
	cout << primes[N-1] << "\n";
	return 0;
}