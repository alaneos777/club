#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using comp = complex<lli>;

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

comp power(comp a, lli b){
	comp ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
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
	return {abs(w0), abs(w1)};
}

lli sqrtMod(lli a, lli p){
	if(a == 0) return 0;
	if(p == 2) return 1;
	if(powerMod(a, (p - 1) / 2, p) != 1) return -1;
	if(p % 4 == 3) return powerMod(a, (p + 1) / 4, p);
	lli s = p - 1;
	int r = 0;
	while((s & 1) == 0) ++r, s >>= 1;
	lli n = 2;
	while(powerMod(n, (p - 1) / 2, p) != p - 1) ++n;
	lli x = powerMod(a, (s + 1) / 2, p);
	lli b = powerMod(a, s, p);
	lli g = powerMod(n, s, p);
	while(true){
		lli t = b;
		int m = 0;
		for(; m < r; ++m){
			if(t == 1) break;
			t = t * t % p;
		}
		if(m == 0) return x;
		lli gs = powerMod(g, 1 << (r - m - 1), p);
		g = gs * gs % p;
		x = x * gs % p;
		b = b * g % p;
		r = m;
	}
}

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const int M = 3e7;
//const int L = sqrtl(36ll*M*M - 12*M + 2);
const int L = 500;
const auto primes = sieve(L);
vector<comp> bases(L+1);

auto gen(const vector<pair<int, int>>& f){
	set<pair<int, int>> s;
	vector<vector<comp>> lists;
	for(const auto & [p,e] : f){
		vector<comp> list;
		if(p == 2){
			list.push_back(power({1, 1}, e));
		}else if(p % 4 == 1){
			comp base_p = bases[p];
			for(int i = 0; i <= e; ++i){
				list.push_back(power(base_p, i) * conj(power(base_p, e-i)));
			}
		}
		lists.push_back(list);
	}
	function<void(int, comp)> rec = [&](int idx, comp acum){
		if(idx == lists.size()){
			int a = abs(acum.real());
			int b = abs(acum.imag());
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

/*
smallest z such that number of (x,y) with (6x-1)^2 + (6y-1)^2 = (6z-1)^2 + 1 and x <= y is over 100
(6z-1)^2 + 1 = 0 mod p
z = (1 +- i) / 6 mod p
*/

int main(){
	vector<lli> acum(M+1);
	vector<vector<pair<int, int>>> facts(M+1);
	for(lli i = 1; i <= M; ++i){
		acum[i] = 36*i*i - 12*i + 2;
	}
	for(int p : primes){
		vector<int> roots;
		if(p == 2){
			roots = {0, 1};
		}else if(p%4 == 1){
			bases[p] = sq2(p);
			lli I = sqrtMod(p-1, p);
			int r0 = (1 + I) * powerMod(6, p-2, p) % p;
			int r1 = (1 - I) * powerMod(6, p-2, p) % p;
			if(r1 < 0) r1 += p;
			roots = {r0, r1};
		}
		for(int root : roots){
			for(int i = root; i <= M; i += p){
				if(i == 0) continue;
				int a = 0;
				while(acum[i] % p == 0){
					acum[i] /= p;
					a++;
				}
				facts[i].emplace_back(p, a);
			}
		}
	}
	/*for(int i = 1; i <= M; ++i){
		if(acum[i] > 1){
			facts[i].emplace_back(acum[i], 1);
		}
	}*/
	for(lli i = 1; i <= M; ++i){
		if(acum[i] > 1) continue;
		lli n = i*(3*i-1)/2;
		int ways = 0;
		for(auto[x,y] : gen(facts[i])){
			if((x+1)%6==0 && (y+1)%6==0){
				x = (x+1)/6;
				y = (y+1)/6;
				ways++;
			}
		}
		if(ways > 100){
			cout << n << " -> " << ways << "\n";
			break;
		}
	}
	return 0;
}