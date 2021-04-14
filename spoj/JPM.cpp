#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

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

const auto primes = sieve(50000);
const int inf = 30000;

short int mem[2][50001];

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for(int pos = 0; pos <= primes.size(); ++pos){
		for(int sum = 0; sum <= 50000; ++sum){
			short int& ans = mem[pos&1][sum];
			if(pos == 0){
				if(sum == 0) ans = 0;
				else ans = inf;
			}else{
				ans = mem[(pos-1)&1][sum];
				if(sum - primes[pos-1] >= 0){
					ans = min(ans, (short int)(mem[(pos-1)&1][sum - primes[pos-1]] + 1));
				}
			}
		}
	}
	int t;
	cin >> t;
	for(int caso = 1; caso <= t; ++caso){
		int n;
		cin >> n;
		int ans = mem[primes.size()&1][n];
		if(ans >= inf) ans = -1;
		cout << "Case " << caso << ": " << ans << "\n";
	}
	return 0;
}