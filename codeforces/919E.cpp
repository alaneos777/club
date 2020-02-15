#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli piso(lli a, lli b){
	lli ans = a / b;
	if(a < 0 && a % b != 0) ans--;
	return ans;
}

map<lli, int> factorize(lli n){
	map<lli, int> f;
	for(lli p = 2; p*p <= n; ++p){
		int pot = 0;
		while(n % p == 0){
			n /= p;
			pot++;
		}
		if(pot) f[p] = pot;
	}
	if(n > 1) f[n] = 1;
	return f;
}

lli power(lli a, lli n){
	lli ans = 1;
	while(n){
		if(n & 1) ans = ans * a;
		n >>= 1;
		a = a * a;
	}
	return ans;
}

lli powerMod(lli a, lli n, lli m){
	lli ans = 1;
	while(n){
		if(n & 1) ans = ans * a % m;
		n >>= 1;
		a = a * a % m;
	}
	return ans;
}

lli order(lli x, lli m){
	lli order = m-1;
	auto f = factorize(order);
	for(auto & factor : f){
		lli p = factor.first;
		int a = factor.second;
		order /= power(p, a);
		lli tmp = powerMod(x, order, m);
		while(tmp != 1){
			tmp = powerMod(tmp, p, m);
			order *= p;
		}
	}
	return order;
}

int main(){
	lli a, b, p, x;
	cin >> a >> b >> p >> x;

	vector<lli> log_a(p, -1), a_pw(p), inv(p, 1);
	lli pw = 1;
	for(int i = 0; i < p; ++i){
		log_a[pw] = i % (p-1);
		a_pw[i] = pw;
		pw = pw * a % p;
	}
	for(int i = 2; i < p; ++i){
		inv[i] = p - (p/i) * inv[p%i] % p;
	}

	lli period = p*order(a, p);

	lli cnt = 0;
	for(lli i = 1; i < p; ++i){
		lli rhs = b * inv[(i * a_pw[i]) % p] % p;
		lli k0 = log_a[rhs];
		if(k0 == -1) continue;
		lli n = i + k0*p;
		cnt += max(0ll, 1 + piso(x - n, period) + piso(n - 1, period));
	}

	cout << cnt << "\n";
	return 0;
}