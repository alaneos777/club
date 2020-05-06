#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto sieve(int n){
	vector<lli> divs(n+1);
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			divs[j] += (lli)i*i;
		}
	}
	return divs;
}

const int M = (int)64e6 - 1;
const auto divs = sieve(M);

bool isSq(lli n){
	lli l = 1, r = 3e9, x;
	while(l <= r){
		lli m = (l + r) / 2;
		if(m*m <= n){
			x = m;
			l = m + 1;
		}else{
			r = m - 1;
		}
	}
	return x*x == n;
}

int main(){
	lli sum = 0;
	for(int n = 1; n <= M; ++n){
		if(isSq(divs[n])){
			//cout << n << " " << (int64_t)divs[n] << "\n";
			sum += n;
		}
	}
	cout << sum << "\n";
	return 0;
}