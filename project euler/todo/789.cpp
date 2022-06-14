#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

tuple<lli, lli, lli> extgcd(lli a, lli b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		lli q = a/b;
		auto[d, x, y] = extgcd(b, a-b*q);
		return {d, y, x-y*q};
	}
}

lli inverse(lli a, lli m){
	auto[d, ans, _] = extgcd(a, m);
	assert(d == 1);
	if(ans < 0) ans += m;
	return ans;
}

lli f(lli p){
	lli ans = 1e18;
	for(lli i = 2; i <= p-2; ++i){
		lli j = inverse(i, p);
		ans = min({ans, (p-3)/2 - 1 + (p-1)*i%p + j, (p-3)/2 - 1 + (p-1)*j%p + i});
	}
	return ans;
}

auto g(int p){
	int ans = 1e9;
	vector<int> pi(p-1), mini;
	iota(pi.begin(), pi.end(), 1);
	do{
		int cost = 0;
		for(int i = 0; i < (p-1)/2; ++i){
			cost += pi[i]*pi[i+(p-1)/2] % p;
		}
		if(cost < ans){
			ans = cost;
			mini = pi;
		}
	}while(next_permutation(pi.begin(), pi.end()));
	return mini;
}

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

int main(){
	for(int x : g(13)){
		cout << x << " ";
	}
	return 0;
	vector<int> primes = sieve(100);
	for(int p : primes){
		if(p == 2) continue;
		cout << p << " " << f(p) << "\n";
	}
	return 0;
}