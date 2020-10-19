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
			s.emplace(b, a);
			s.emplace(a, -b);
			s.emplace(-b, a);
			s.emplace(-a, b);
			s.emplace(b, -a);
			s.emplace(-a, -b);
			s.emplace(-b, -a);
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

const ld pi = acosl(-1);

struct pt{
	int x, y, z;
	pt(): x(0), y(0), z(0) {}
	pt(ld x, ld y, ld z): x(x), y(y), z(z) {}
	lli dot(const pt & p) const{return (lli)x*p.x + (lli)y*p.y + (lli)z*p.z;}
	pt cross(const pt & p) const{return pt(y*p.z - z*p.y, -x*p.z + z*p.x, x*p.y - y*p.x);}
	ld norm() const{return x*x + y*y + z*z;}
	ld len() const{return sqrt(x*x + y*y + z*z);}
};

ld angle(const pt & a, const pt & b, const pt & c){
	pt n1 = a.cross(b);
	pt n2 = a.cross(c);
	return acos(n1.dot(n2) / (n1.len() * n2.len()));
}

ld A(int r){
	vector<pt> p;
	for(int x = 0; x <= r; ++x){
		map<int, int> fact;
		factorice(r + x, fact);
		factorice(r - x, fact);
		auto sols = r2(r*r - x*x, fact);
		for(const comp & sol : sols){
			p.emplace_back(sol.real(), sol.imag(), x);
		}
	}

	int n = p.size();
	ld ans = 1e9;
	for(int i = 0; i < n-2; ++i){
		for(int j = i+1; j < n-1; ++j){
			for(int k = j+1; k < n; ++k){
				if(p[i].cross(p[j]).dot(p[k]) == 0) continue;
				ld a = angle(p[i], p[j], p[k]);
				ld b = angle(p[j], p[k], p[i]);
				ld c = angle(p[k], p[i], p[j]);
				ans = min(ans, a+b+c-pi);
			}
		}
	}
	return ans * r * r;
}

int main(){
	ld ans = 0;
	for(int i = 1; i <= 50; ++i){
		ans += A(i);
	}
	cout << fixed << setprecision(6) << ans << "\n";
	return 0;
}