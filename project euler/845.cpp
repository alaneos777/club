#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto isSieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	is[0] = is[1] = false;
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			is[d] = false;
			if(i%p == 0) break;
		}
	}
	return is;
}

const auto isPrime = isSieve(200);

lli mem[25][200][2];

lli f(const string& N, int pos, int sum, bool canUseAll){
	if(pos == N.size()) return isPrime[sum];
	lli& ans = mem[pos][sum][canUseAll];
	if(ans != -1) return ans;
	ans = 0;
	int curr = N[pos]-'0';
	int lim = canUseAll ? 9 : curr;
	for(int d = 0; d <= lim; ++d){
		ans += f(N, pos+1, sum+d, canUseAll | (d < curr));
	}
	return ans;
}

lli D(lli n){
	lli ans = -1, l = 1, r = 1e18;
	while(l <= r){
		memset(mem, -1, sizeof(mem));
		lli m = l + (r-l)/2;
		if(f(to_string(m), 0, 0, false) >= n){
			ans = m;
			r = m-1;
		}else{
			l = m+1;
		}
	}
	return ans;
}

int main(){
	cout << D(1e16) << "\n";
	return 0;
}