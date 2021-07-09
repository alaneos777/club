#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

tuple<lli, lli, lli> extendedGcd(lli a, lli b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		auto[d, x, y] = extendedGcd(b, a%b);
		return {d, y, x - y*(a/b)};
	}
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

lli powerMod(lli a, lli b, lli mod){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

auto fact(lli n){
	vector<pair<lli, int>> f;
	for(lli p = 2; p*p <= n; ++p){
		int e = 0;
		while(n % p == 0){
			n /= p;
			e++;
		}
		if(e) f.emplace_back(p, e);
	}
	if(n > 1) f.emplace_back(n, 1);
	return f;
}

lli phi(lli n){
	lli ans = n;
	for(auto[p, a]: fact(n)){
		ans -= ans/p;
	}
	return ans;
}

lli multiplicativeOrder(lli a, lli m){
	assert(__gcd(a, m) == 1);
	lli ord = phi(m), ans = ord;
	for(auto[p, e] : fact(ord)){
		lli pe = power(p, e);
		ans /= pe;
		while(powerMod(a, ans, m) != 1){
			ans *= p;
		}
	}
	return ans;
}

pair<lli, lli> discreteLogarithm(lli a, lli b, lli m){
	if(m == 1) return {0, 1};
	if(a == 0 && b == 0) return {1, 1};
	lli m1 = m, pw = 1, div, nonRep = 0;
	for(; (div = __gcd(a, m1)) > 1; ++nonRep, m1 /= div, pw = pw * a % m){
		if(pw == b) return {nonRep, 0}; //aperiodic solution found
	}
	auto[d, x, y] = extendedGcd(pw, m);
	if(b % d > 0) return {-1, 0}; //solution not found
	b = x * (b / d) % m;
	if(b < 0) b += m;
	lli order = multiplicativeOrder(a, m1);
	lli n = sqrt(order) + 1;
	lli a_n = powerMod(a, n, m1);
	unordered_map<lli, lli> firstHalf;
	pw = a_n;
	for(lli p = 1; p <= n; ++p, pw = pw * a_n % m1){
		firstHalf[pw] = p;
	}
	pw = b % m1;
	for(lli q = 0; q <= n; ++q, pw = pw * a % m1){
		if(firstHalf.count(pw)) return {nonRep + (n * firstHalf[pw] - q) % order, order}; //periodic solution found
	}
	return {-1, 0}; //solution not found
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli x, y, m;
		cin >> x >> y >> m;
		auto[k, _] = discreteLogarithm(x, y, m);
		cout << k << "\n";
	}
	return 0;
}