#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
using ld = double;
using comp = complex<lli>;

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans % m;
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
	return {lli(abs(w0)), lli(abs(w1))};
}

auto sieve(int n){
	vector<int> primes, lp(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0) primes.push_back(i), lp[i] = i;
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			lp[d] = p;
			if(p == lp[i]) break;
		}
	}
	return lp;
}

struct comparer{
	bool operator() (const comp & a, const comp & b) const{
		return a.real() < b.real() || (a.real() == b.real() && a.imag() < b.imag());
	}
};

set<comp, comparer> r2(lli n, const map<int, int> & fact){
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

const int N = 1 << 15; //5^10
const auto lp = sieve(2*N);

void factorice(int n, map<int, int> & fact){
	while(n > 1){
		int p = lp[n];
		int e = 0;
		while(n % p == 0){
			n /= p;
			e++;
		}
		fact[p] += e;
	}
}

using pt = tuple<int, int, int>;
const ld pi = acos(-1);

ld arc(const pt & a, const pt & b){
	ld x0, y0, z0, x1, y1, z1;
	tie(x0, y0, z0) = a;
	tie(x1, y1, z1) = b;
	ld cosine = (x0*x1 + y0*y1 + z0*z1) / sqrt(x0*x0 + y0*y0 + z0*z0) / sqrt(x1*x1 + y1*y1 + z1*z1);
	return acos(cosine);
}

ld M(int r){
	vector<pt> p;
	for(int x = 0; x <= r; ++x){
		map<int, int> fact;
		factorice(r + x, fact);
		factorice(r - x, fact);
		auto sols = r2(r*r - x*x, fact);
		for(const comp & sol : sols){
			p.emplace_back(sol.real(), sol.imag(), x);
			if(x) p.emplace_back(sol.real(), sol.imag(), -x);
		}
	}

	int n = p.size();
	int start, end;
	for(int i = 0; i < n; ++i){
		if(p[i] == pt{0, 0, r}){
			start = i;
		}else if(p[i] == pt{0, 0, -r}){
			end = i;
		}
	}

	vector<ld> dis(n, 1e9);
	vector<bool> vis(n);
	cout << n << "\n";
	dis[start] = 0;
	vis[start] = true;
	priority_queue<pair<ld, int>, vector<pair<ld, int>>, greater<pair<ld, int>>> q;
	q.emplace(0, start);

	while(!q.empty()){
		int u = q.top().second;
		double tmp = q.top().first;
		q.pop();
		if(dis[u] < tmp) continue;
		vis[u] = true;
		if(u == end) return dis[u] / (pi * pi);
		for(int v = 0; v < n; ++v){
			if(v == u || vis[v]) continue;
			ld risk = arc(p[u], p[v]);
			risk = risk * risk;
			if(dis[u] + risk < dis[v]){
				dis[v] = dis[u] + risk;
				q.emplace(dis[v], v);
			}
		}
	}
}

int main(){
	ld ans = 0;
	for(int i = 1; i <= 15; ++i){
		ans += M((1<<i) - 1);
	}
	cout << fixed << setprecision(10) << ans << "\n";
	return 0;
}