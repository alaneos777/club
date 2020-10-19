#include <bits/stdc++.h>
using namespace std;

int mem[11][100][2];

auto sieve(int n){
	vector<int> primes;
	vector<bool> isPrime(n+1, true);
	isPrime[0] = isPrime[1] = false;
	for(int i = 2; i < n; ++i){
		if(isPrime[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0) break;
		}
	}
	return isPrime;
}

const auto isPrime = sieve(100);

int f(int pos, int sum, bool canUseAll, const string & num){
	if(pos == num.size()){
		return isPrime[sum];
	}
	int & ans = mem[pos][sum][canUseAll];
	if(ans != -1) return ans;
	ans = 0;
	int limit = canUseAll ? 9 : num[pos] - '0';
	for(int d = 0; d <= limit; ++d){
		ans += f(pos + 1, sum + d, canUseAll | d != limit, num);
	}
	return ans;
}

int f(int n){
	memset(mem, -1, sizeof(mem));
	string num = to_string(n);
	return f(0, 0, false, num);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		int l, r;
		cin >> l >> r;
		int ans = f(r);
		if(l) ans -= f(l-1);
		cout << ans << "\n";
	}
	return 0;
}