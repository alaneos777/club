#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
using ld = long double;
using LLI = __int128;

LLI powerMod(LLI a, LLI b, LLI m){
	LLI ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans % m;
}

bool isPrime(lli n){
	if(n < 2) return false;
	if(!(n & 1)) return n == 2;
	lli d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
		if(n == a) return true;
		lli m = powerMod(a, d, n);
		if(m == 1 || m == n - 1) continue;
		int k = 0;
		for(; k < s; ++k){
			m = (LLI)m * m % n;
			if(m == n - 1) break;
		}
		if(k == s) return false;
	}
	return true;
}

lli getFactor(lli n){
	lli a = 1 + rand() % (n - 1), b = 1 + rand() % (n - 1);
	lli x = 2, y = 2, d = 1;
	while(d == 1){
		x = (LLI)x * ((LLI)x + b) % n + a;
		y = (LLI)y * ((LLI)y + b) % n + a;
		y = (LLI)y * ((LLI)y + b) % n + a;
		d = __gcd(abs(x - y), n);
	}
	return d;
}

map<lli, int> fact;
void factorice(lli n, bool clean = true){
	if(clean) fact.clear();
	while(n > 1 && !isPrime(n)){
		lli f = n;
		for(; f == n; f = getFactor(n));
		n /= f;
		factorice(f, false);
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
	srand(time(0));
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli x;
		cin >> x;
		factorice(x);
		lli ans = 0;
		for(const auto & par : fact){
			lli p; int a;
			tie(p, a) = par;
			ans += x / p * a;
		}
		cout << ans << "\n";
	}
	return 0;
}