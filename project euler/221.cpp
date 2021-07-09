#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

bool isPrimeMillerRabin(lli n){
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
			m = m * m % n;
			if(m == n - 1) break;
		}
		if(k == s) return false;
	}
	return true;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
lli aleatorio(lli a, lli b){
	std::uniform_int_distribution<lli> dist(a, b);
	return dist(rng);
}
lli getFactor(lli n){
	lli a = aleatorio(1, n - 1), b = aleatorio(1, n - 1);
	lli x = 2, y = 2, d = 1;
	while(d == 1){
		x = x * ((x + b) % n) % n + a;
		y = y * ((y + b) % n) % n + a;
		y = y * ((y + b) % n) % n + a;
		d = __gcd(max(x - y, y - x), n);
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

vector<lli> divs(lli n){
	factorizePollardRho(n);
	vector<lli> ans;
	function<void(map<lli, int>::iterator, lli)> f = [&](map<lli, int>::iterator it, lli x){
		if(it == fact.end()){
			ans.push_back(x);
		}else{
			auto[p, a] = *it;
			lli p_pow = 1;
			auto it2 = it; ++it2;
			for(int i = 0; i <= a; ++i){
				f(it2, x * p_pow);
				p_pow *= p;
			}
		}
	};
	f(fact.begin(), 1);
	return ans;
}

ostream &operator<<(ostream &os, const __int128 & value){
	char buffer[64];
	char *pos = end(buffer) - 1;
	*pos = '\0';
	__int128 tmp = value < 0 ? -value : value;
	do{
		--pos;
		*pos = tmp % 10 + '0';
		tmp /= 10;
	}while(tmp != 0);
	if(value < 0){
		--pos;
		*pos = '-';
	}
	return os << pos;
}

int main(){
	set<lli> st;
	for(lli n = 1; n <= 80000; ++n){
		for(lli d : divs(n*n+1)){
			st.insert(n * (n+d) * (n + (n*n+1)/d));
		}
	}
	int cnt = 0;
	for(lli a : st){
		cnt++;
		if(cnt == 150000){
			cout << a << "\n";
			break;
		}
	}
	return 0;
}