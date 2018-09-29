#include <bits/stdc++.h>
using namespace std;
typedef __int128 lli;
typedef long long int ll;

lli gcd(lli a, lli b){
	lli r;
	while(b != 0) r = a % b, a = b, b = r;
	return a;
}

lli powMod(lli b, lli e, lli m){
	lli ans = 1;
	b %= m;
	while(e){
		if(e & 1) ans = (ans * b) % m;
		e >>= 1;
		b = (b * b) % m;
	}
	return ans;
}

bool isPrime(lli n){
	if(n < 2) return false;
	if(n == 2) return true;
	lli d = n - 1, s = 0;
	while(!(d & 1)){
		d >>= 1;
		++s;
	}
	for(int i = 0; i < 16; ++i){
		lli a = 1 + rand() % (n - 1);
		lli m = powMod(a, d, n);
		if(m == 1 || m == n - 1) goto exit;
		for(int k = 0; k < s - 1; ++k){
			m = m * m % n;
			if(m == n - 1) goto exit;
		}
		return false;
		exit:;
	}
	return true;
}

ll getFactor(ll n){
	lli a = 1 + rand() % (n - 1);
	lli b = 1 + rand() % (n - 1);
	lli x = 2, y = 2;
	ll d = 1;
	while(d == 1 || d == -1){
		x = x * (x + b) % n + a;
		y = y * (y + b) % n + a;
		y = y * (y + b) % n + a;
		d = gcd(x - y, n);
	}
	return abs(d);
}

map<ll, ll> fact; //don't forget to clean
void factorize(ll n){
	while(n > 1 && !isPrime(n)){
		ll f;
		do{
			f = getFactor(n);
		}while(f == n);
		n /= f;
		factorize(f);
		for(auto & it : fact){
			while(n % it.first == 0){
				n /= it.first;
				++it.second;
			}
		}
	}
	if(n > 1) ++fact[n];
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		ll p, r, m, n;
		cin >> p >> r >> m >> n;
		fact.clear();
		factorize(m + 1);
		if(fact[p]*n >= r){
			cout << "Lo lograste\n";
		}else{
			cout << "Sad eyes\n";
		}
	}
	return 0;
}