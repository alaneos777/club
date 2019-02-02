#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 998244353;

lli gcd(lli a, lli b){
	lli r;
	while(b) r = a % b, a = b, b = r;
	return a;
}

lli multMod(lli a, lli b, lli m){
	a %= m, b %= m;
	lli ans = 0;
	while(b){
		if(b & 1) ans = (ans + a) % m;
		b >>= 1;
		a = (a + a) % m;
	}
	return ans;
}

lli powerMod(lli a, lli b, lli m){
	a %= m;
	lli ans = 1;
	while(b){
		if(b & 1) ans = multMod(ans, a, m);
		b >>= 1;
		a = multMod(a, a, m);
	}
	return ans;
}

bool isPrimeMillerRabin(lli n){
	if(n < 2) return false;
	if(n == 2) return true;
	lli d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int i = 0; i < 16; ++i){
		lli a = 1 + rand() % (n - 1);
		lli m = powerMod(a, d, n);
		if(m == 1 || m == n - 1) goto exit;
		for(int k = 0; k < s; ++k){
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
	while(d == 1){
		x = multMod(x, x + b, n) + a;
		y = multMod(y, y + b, n) + a;
		y = multMod(y, y + b, n) + a;
		d = gcd(abs(x - y), n);
	}
	return d;
}

map<lli, int> fact;
void factorizePollardRho(lli n, bool clean = true){
	if(clean) fact.clear();
	while(n > 1 && !isPrimeMillerRabin(n)){
		lli f = n;
		for(; f == n; f = getFactor(n));
		n /= f;
		factorizePollardRho(f, false);
		for(auto & it : fact){
			while(n % it.first == 0){
				n /= it.first;
				++it.second;
			}
		}
	}
	if(n > 1) ++fact[n];
}

lli mu2(map<lli, int> & f){
	lli ans = 1;
	for(auto par : f){
		if(par.second == 0 || par.second == 2){
			ans *= 1;
		}else if(par.second == 1){
			ans *= -2;
		}else{
			return 0;
		}
	}
	return ans;
}

lli div(map<lli, int> & f){
	lli ans = 1;
	for(auto par : f){
		ans *= par.second + 1;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lli n;
	cin >> n;
	factorizePollardRho(n);
	lli ans = 0;
	function<void(map<lli, int>::iterator, map<lli, int>, map<lli, int>)> dfs = [&](map<lli, int>::iterator it, map<lli, int> f, map<lli, int> fc){
		if(it == fact.end()){
			lli t = mu2(f);
			lli d0 = div(fc);
			ans += t * (powerMod(2, d0, mod) - 1) % mod;
			while(ans >= mod) ans -= mod;
			while(ans < 0) ans += mod;
		}else{
			lli p = it->first;
			int a = it->second;
			auto acum = f;
			auto acumc = fc;
			for(int i = 0; i <= a; ++i){
				auto it2 = it; it2++;
				dfs(it2, acum, acumc);
				acum[p]++;
				acumc[p]--;
				if(acumc[p] == 0) acumc.erase(p);
			}
		}
	};
	dfs(fact.begin(), {}, fact);
	cout << ans << "\n";
	return 0;
}