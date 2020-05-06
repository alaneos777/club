#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
using comp = complex<lli>;

const lli M = 2.5e7;

auto lpSieve(int n){
	vector<int> lp(n+1, 1);
	lp[0] = lp[1] = 0;
	for(int i = 2; i <= n; ++i) lp[i] = (i&1 ? i : 2);
	for(int i = 3; i*i <= n; i += 2){
		if(lp[i] == i){
			for(int j = i*i; j <= n; j += 2*i){
				if(lp[j] == j) lp[j] = i;
			}
		}
	}
	return lp;
}

const auto lp = lpSieve(sqrt(M*M + 1) + 100);

__int128 powerMod(__int128 a, __int128 b, __int128 m){
	__int128 ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
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

auto factsSieve(int n){
	vector<lli> acum(n+1);
	vector<vector<pair<lli, int>>> facts(n+1);
	for(lli i = 0; i <= n; ++i){
		acum[i] = i*i + 1;
	}
	for(int p = 2; p < lp.size(); ++p){
		if(lp[p] != p) continue;
		if(p % 4 == 3) continue;
		lli r0 = sqrtMod(p-1, p);
		if(r0 == -1) continue;
		lli r1 = (p - r0) % p;
		vector<lli> roots = {r0};
		if(r0 != r1) roots.push_back(r1);
		for(lli root : roots){
			for(lli i = root; i <= n; i += p){
				int e = 0;
				while(acum[i] % p == 0){
					acum[i] /= p;
					++e;
				}
				facts[i].emplace_back(p, e);
			}
		}
	}
	for(int i = 0; i <= n; ++i){
		if(acum[i] > 1){
			facts[i].emplace_back(acum[i], 1);
		}
	}
	return facts;
}

const auto facts = factsSieve(M);

comp sq2(__int128 p){
	assert(p >= 3 && p % 4 == 1);
	__int128 z;
	for(__int128 a = 2; a < p-1; ++a){
		if(powerMod(a, (p-1)/2, p) == p-1){
			z = powerMod(a, (p-1)/4, p);
			break;
		}
	}
	__int128 w0 = p, w1 = 0, z0 = z, z1 = 1;
	while(z0 || z1){
		__int128 n = z0*z0 + z1*z1;
		__int128 u0 = (w0*z0 + w1*z1) / n;
		__int128 u1 = (w1*z0 - w0*z1) / n;
		__int128 r0 = w0 - z0*u0 + z1*u1;
		__int128 r1 = w1 - z0*u1 - z1*u0;
		w0 = z0, w1 = z1, z0 = r0, z1 = r1;
	}
	return {lli(abs(w0)), lli(abs(w1))};
}

vector<vector<comp>> base(M+1);

comp power(comp a, lli b){
	comp ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

set<pair<lli, lli>> sq2(const vector<pair<lli, int>> & f){
	set<pair<lli, lli>> ans;
	vector<vector<comp>> lists;
	for(const auto & par : f){
		lli p; int e;
		tie(p, e) = par;
		if(p % 4 == 3 && e % 2 == 1) return {};
	}
	for(const auto & par : f){
		lli p; int e;
		tie(p, e) = par;
		vector<comp> list;
		if(p == 2){
			list.push_back(base[p][e]);
		}else if(p % 4 == 3){
			if(p < base.size()){
				list.push_back(base[p][e/2]);
			}else{
				list.push_back(power({p, 0}, e/2));
			}
		}else{
			if(p < base.size()){
				for(int i = 0; i <= e; ++i){
					list.push_back(base[p][i] * conj(base[p][e-i]));
				}
			}else{
				comp base_p = sq2(p);
				for(int i = 0; i <= e; ++i){
					list.push_back(power(base_p, i) * conj(power(base_p, e-i)));
				}
			}
		}
		lists.push_back(list);
	}
	function<void(int, comp)> rec = [&](int idx, comp acum){
		if(idx == lists.size()){
			lli re = abs(acum.real());
			lli im = abs(acum.imag());
			if(re > im) swap(re, im);
			ans.emplace(re, im);
		}else{
			for(int i = 0; i < lists[idx].size(); ++i){
				rec(idx + 1, acum * lists[idx][i]);
			}
		}
	};
	rec(0, 1);
	return ans;
}

int main(){
	for(int p = 3; p <= M; p += 2){
		if(lp[p] == p){
			base[p].emplace_back(1, 0);
			base[p].push_back(p % 4 == 1 ? sq2(p) : comp{p, 0});
			for(lli p_pow = p*p; p_pow <= M*M+1; p_pow *= p){
				base[p].push_back(base[p][1] * base[p].back());
			}
		}
	}
	base[2].emplace_back(1, 0);
	base[2].emplace_back(1, 1);
	for(lli p_pow = 4; p_pow <= M*M+1; p_pow *= 2){
		base[2].push_back(base[2][1] * base[2].back());
	}

	lli cnt = 0;
	for(lli c = 1; c <= M; ++c){
		auto sols = sq2(facts[c]);
		if(!sols.empty()){
			for(auto sol : sols){
				lli a = sol.first, b = sol.second;
				if(a+b+c <= M){
					assert(a*a + b*b == c*c + 1);
					assert(a+b>c && a+c>b && b+c>a);
					cnt++;
				}
			}
		}
	}
	cout << cnt << "\n";
	return 0;
}