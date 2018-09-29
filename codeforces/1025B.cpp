#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli gcd(lli a, lli b){
	lli r;
	while(b) r=a%b, a=b, b=r;
	return a;
}

lli lcm(lli a, lli b){
	return a*(b/gcd(a,b));
}

lli multMod(lli a, lli b, lli n){
	lli ans = 0;
	a %= n, b %= n;
	if(abs(b) > abs(a)) swap(a, b);
	if(b < 0){
		a *= -1, b *= -1;
	}
	while(b){
		if(b & 1) ans = (ans + a) % n;
		b >>= 1;
		a = (a + a) % n;
	}
	return ans;
}

lli powMod(lli b, lli e, lli m){
	lli ans = 1;
	b %= m;
	while(e){
		if(e & 1) ans = multMod(ans, b, m);
		e >>= 1;
		if(e) b = multMod(b, b, m);
	}
	return ans;
}

bool isPrimeMillerRabin(lli n){
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
			m = multMod(m, m, n);
			if(m == n - 1) goto exit;
		}
		return false;
		exit:;
	}
	return true;
}

lli getFactor(lli n){
	lli a = 1 + rand() % (n - 1);
	lli b = 1 + rand() % (n - 1);
	lli x = 2, y = 2, d = 1;
	while(d == 1 || d == -1){
		x = multMod(x, x+b, n) + a;
		y = multMod(y, y+b, n) + a;
		y = multMod(y, y+b, n) + a;
		d = gcd(x - y, n);
	}
	return abs(d);
}

map<lli, int> fact; //don't forget to clean
void factorizePollardRho(lli n){
	while(n > 1 && !isPrimeMillerRabin(n)){
		lli f;
		do{
			f = getFactor(n);
		}while(f == n);
		n /= f;
		factorizePollardRho(f);
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
	srand(time(NULL));
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	lli ans = 0, x, y;
	for(int i = 0; i < n; ++i){
	    cin >> x >> y;
	    ans = gcd(ans, lcm(x, y));
	}
	factorizePollardRho(ans);
	ans = (fact.size()>0 ? fact.begin()->first : -1);
	cout << ans << "\n";
	return 0;
}