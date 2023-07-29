#include <bits/stdc++.h>
using namespace std;

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

const int M = 1e6;
const auto primes = sieve(M-1);

int main(){
	double sum = 0;
	int cnt = 0;
	for(int p : primes){
		if(p == 2) continue;
		sum += 7.0/18.0 + 4.0/(9*(p+1));
		cnt++;
	}
	cout << fixed << setprecision(10) << sum/cnt << "\n";
	return 0;
}