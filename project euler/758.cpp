#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

tuple<lli, lli, lli> extgcd(lli a, lli b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		auto[d, x, y] = extgcd(b, a%b);
		return {d, y, x-y*(a/b)};
	}
}

lli power(lli a, lli b){
	lli ans = 1;
	a %= mod;
	b %= mod-1;
	while(b){
		if(b&1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int Q(int a, int b){
	if(a == 1 || b == 1) return 0;
	int x = 0, y = 0;
	int ans = 0;
	while(true){
		if(x == 0){
			x = a;
			ans++;
		}else if(y == b){
			y = 0;
			ans++;
		}else{
			int t = min(x, b - y);
			x -= t, y += t;
			ans++;
			if(x == 1 || y == 1) return ans;
		}
	}
	return -1;
}

int P(int a, int b){
	return min(Q(a, b), Q(b, a));
}

lli R(lli a, lli b){
	auto[_, x, y] = extgcd(a, b);
	return 2 * (abs(x) + abs(y) - 1);
}

tuple<lli, lli, lli, int> Extgcd(lli a, lli b){
	if(b == 0){
		return {a, power(2, a)-1, 0, 0};
	}else{
		lli q = a/b, r = a-b*q;
		auto[d, x, y, steps] = Extgcd(b, r);
		lli quot = (power(2, a) - power(2, r)) * power(power(2, b) - 1, mod-2) % mod;
		lli nxt_x = x - y * quot % mod;
		if(nxt_x < 0) nxt_x += mod;
		return {d, y, nxt_x, steps+1};
	}
}

auto sieve(int n){
	vector<int> primes; vector<bool> is(n+1, true);
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

const int M = 1000-1;
const auto primes = sieve(M);

int main(){
	/*for(int a = 1; a <= 1000; ++a){
		for(int b = 1; b <= 1000; ++b){
			if(__gcd(a, b) == 1){
				assert(P(a, b) == R(a, b));
			}
		}
	}*/
	lli sum = 0;
	for(int i = 0; i < primes.size(); ++i){
		for(int j = 0; j < i; ++j){
			lli a = primes[i], b = primes[j];
			a = a*a*a*a*a;
			b = b*b*b*b*b;
			auto[d, x, y, steps] = Extgcd(a, b);
			assert(d == 1);
			lli ans = 0;
			if(steps%2 == 0){ // y<0, x>0
				ans = 2 * (x - y - 1) % mod;
			}else{ // y>0, x<0
				ans = 2 * (y - x - 1) % mod;
			}
			if(ans < 0) ans += mod;
			sum += ans;
			if(sum >= mod) sum -= mod;
			//cout << "(" << a << ", " << b << ") -> " << ans << "\n";
		}
	}
	cout << sum << "\n";
	return 0;
}