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
			if(i%p == 0) break;
		}
	}
	return primes;
}

const int M = 1e5;
const vector<int> primes = sieve(M);

inline lli p(int t){
	return primes[t];
}

int main(){
	int k = 7000, n = p(7000), r = 2000;
	vector<vector<lli>> mem(r, vector<lli>(k, -1));
	function<lli(int, int)> f = [&](int pos, int sum) -> lli{
		lli& ans = mem[pos][sum];
		if(ans != -1) return ans;
		ans = 0;
		if(pos == r-1){
			int ar = (n-r-sum)%k;
			if(ar < 0) ar += k;
			ans = p(ar);
			return ans;
		}else{
			for(int ai = k-1; ai >= k-10; --ai){
				ans = max(ans, p(ai) + f(pos+1, (sum+ai)%k));
			}
			return ans;
		}
	};
	lli ans = f(0, 0) + (n-r) * p(k-1);
	cout << ans << "\n";
	return 0;
}