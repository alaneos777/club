#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
using comp = complex<lli>;

const lli M = 7.5e7;

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

const auto lp = lpSieve(M+1);

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
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

vector<vector<comp>> base(M+1);

void fact(int n, map<int, int> & f){
	while(n > 1){
		int p = lp[n], e = 0;
		while(n % p == 0){
			n /= p;
			e++;
		}
		f[p] += e;
	}
}

set<pair<lli, lli>> sq2(const map<int, int> & f){
	set<pair<lli, lli>> ans;
	vector<vector<comp>> lists;
	for(const auto & par : f){
		int p, e;
		tie(p, e) = par;
		if(p % 4 == 3 && e % 2 == 1) return {};
	}
	for(const auto & par : f){
		int p, e;
		tie(p, e) = par;
		vector<comp> list;
		if(p == 2){
			list.push_back(base[p][e]);
		}else if(p % 4 == 3){
			list.push_back(base[p][e/2]);
		}else{
			for(int i = 0; i <= e; ++i){
				list.push_back(base[p][i] * conj(base[p][e-i]));
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
			for(lli p_pow = p*p; p_pow <= M; p_pow *= p){
				base[p].push_back(base[p][1] * base[p].back());
			}
		}
	}
	base[2].emplace_back(1, 0);
	base[2].emplace_back(1, 1);
	for(lli p_pow = 4; p_pow <= M; p_pow *= 2){
		base[2].push_back(base[2][1] * base[2].back());
	}

	lli cnt = 0;
	for(lli c = 2; c <= M; ++c){
		map<int, int> f;
		fact(c-1, f);
		fact(c+1, f);
		auto sols = sq2(f);
		if(!sols.empty()){
			for(auto sol : sols){
				lli a = sol.first, b = sol.second;
				if(a+b+c <= M){
					cnt++;
				}
			}
		}
	}
	cout << cnt << "\n";
	return 0;
}