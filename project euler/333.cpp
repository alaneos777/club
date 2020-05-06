#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	is[0] = is[1] = false;
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

const int N = int(1e6);
const auto primes = sieve(N-1);

int main(){
	vector<int> valids(N);
	int a = log2(N), b = log2(N)/log2(3);
	vector<lli> two(a+1, 1), three(b+1, 1);
	for(int i = 1; i <= a; ++i){
		two[i] = two[i-1] * 2;
	}
	for(int i = 1; i <= b; ++i){
		three[i] = three[i-1] * 3;
	}

	function<void(int, int, int)> f = [&](int exp_2, int exp_3, int acum){
		if(acum >= N) return;
		valids[acum]++;
		for(int j = 0; j < exp_3; ++j){
			for(int i = exp_2 + 1; acum + two[i]*three[j] < N; ++i){
				f(i, j, acum + two[i]*three[j]);
			}
		}
	};

	for(int j = 0; j <= b; ++j){
		f(0, j, three[j]);
	}

	lli ans = 0;
	for(int p : primes){
		if(valids[p] == 1){
			ans += p;
		}
	}
	cout << ans+2 << "\n";

	return 0;
}