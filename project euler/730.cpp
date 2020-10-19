#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using LLI = __int128_t;
using comp = complex<lli>;

comp power(comp a, lli b){
	comp ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

LLI powerMod(LLI a, LLI b, LLI m){
	LLI ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans % m;
}

comp sq2(lli p){
	assert(p >= 3 && p % 4 == 1);
	lli z;
	for(lli a = 2; a < p-1; ++a){
		if(powerMod(a, (p-1)/2, p) == p-1){
			z = powerMod(a, (p-1)/4, p);
			break;
		}
	}
	lli w0 = p, w1 = 0, z0 = z, z1 = 1;
	while(z0 || z1){
		lli n = z0*z0 + z1*z1;
		lli u0 = (w0*z0 + w1*z1) / n;
		lli u1 = (w1*z0 - w0*z1) / n;
		lli r0 = w0 - z0*u0 + z1*u1;
		lli r1 = w1 - z0*u1 - z1*u0;
		w0 = z0, w1 = z1, z0 = r0, z1 = r1;
	}
	return {lli(abs(w0)), lli(abs(w1))};
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

struct comparer{
	bool operator() (const comp & a, const comp & b) const{
		return a.real() < b.real() || (a.real() == b.real() && a.imag() < b.imag());
	}
};

set<comp, comparer> r2(lli n){
	if(n == 0) return {{0, 0}};
	set<comp, comparer> s;
	vector<vector<comp>> lists;
	for(const auto & par : fact){
		lli p; int e;
		tie(p, e) = par;
		if(e == 0) continue;
		if(p % 4 == 3 && e % 2 == 1) return {};
	}
	for(const auto & par : fact){
		lli p; int e;
		tie(p, e) = par;
		if(e == 0) continue;
		vector<comp> list;
		if(p == 2){
			list.push_back(power({1, 1}, e));
		}else if(p % 4 == 3){
			list.push_back(power({p, 0}, e/2));
		}else{
			comp base_p = sq2(p);
			for(int i = 0; i <= e; ++i){
				list.push_back(power(base_p, i) * conj(power(base_p, e-i)));
			}
		}
		lists.push_back(list);
	}
	function<void(int, comp)> rec = [&](int idx, comp acum){
		if(idx == lists.size()){
			lli a = abs(acum.real());
			lli b = abs(acum.imag());
			if(a > b) swap(a, b);
			s.emplace(a, b);
		}else{
			for(int i = 0; i < lists[idx].size(); ++i){
				rec(idx + 1, acum * lists[idx][i]);
			}
		}
	};
	rec(0, 1);
	return s;
}

int main(){
	int m = 1e2, n = 1e8;
	lli ans = 0;
	for(int k = 0; k <= m; ++k){
		for(int r = 1; r <= n; ++r){
			if(r % 10000 == 0) cout << k << " " << r << "\n";
			lli rhs = (lli)r*r - k;
			if(rhs <= 0) continue;
			factorice(rhs);
			auto lhs = r2(rhs);
			for(const comp & ci : lhs){
				int a = ci.real(), b = ci.imag();
				if(1 <= a && __gcd(a, __gcd(b, r)) == 1 && a+b+r <= n){
					ans++;
				}
			}
		}
	}
	cout << ans << "\n";
	return 0;
}