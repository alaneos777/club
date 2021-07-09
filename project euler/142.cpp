#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using comp = complex<lli>;

bool isSq(lli n){
	lli r = sqrtl(n);
	return r*r == n;
}

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
		if(b & 1) ans = ans * a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}

pair<lli, lli> sq2(lli p){
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

auto lpSieve(int n){
	vector<int> primes, lp(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			lp[i] = i;
			primes.push_back(i);
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
		}
	}
	return lp;
}

const int M = 1e6;
auto lp = lpSieve(M);

auto fact(int n){
	map<int, int> f;
	while(n > 1){
		int p = lp[n], a = 0;
		while(n % p == 0){
			n /= p;
			a++;
		}
		f[p] = a;
	}
	return f;
}

struct comparer{
	bool operator() (const comp & a, const comp & b) const{
		return a.real() < b.real() || (a.real() == b.real() && a.imag() < b.imag());
	}
};

set<comp, comparer> s(int n){
	set<comp, comparer> ans;
	vector<vector<comp>> lists;
	auto f = fact(n);
	f[2]++;
	for(auto[p, a] : f){
		vector<comp> list;
		if(p == 2){
			list.push_back(power({1, 1}, a));
		}else if(p % 4 == 3){
			if(a%2 == 1) return {};
			list.push_back(power({p, 0}, a/2));
		}else{
			auto[re, im] = sq2(p);
			comp w = {re, im};
			comp z = {re, -im};
			for(int i = 0; i <= a; ++i){
				list.push_back(power(w, i) * power(z, a-i));
			}
		}
		lists.push_back(list);
	}
	function<void(int, comp)> dfs = [&](int pos, comp z){
		if(pos == lists.size()){
			lli a = abs(z.real());
			lli b = abs(z.imag());
			if(a < b) swap(a, b);
			if(b>0 && a!=b) ans.emplace(a, b);
		}else{
			for(comp x : lists[pos]){
				dfs(pos+1, z*x);
			}
		}
	};
	dfs(0, 1);
	return ans;
}

int main(){
	for(int x = 1; x <= M; ++x){
		auto sq = s(x);
		int len = sq.size();
		if(len < 2) continue;
		for(auto it = sq.begin(); it != sq.end(); ++it){
			auto it2 = it;
			for(++it2; it2 != sq.end(); ++it2){
				lli c = it->real(), d = it->imag();
				lli a = it2->real(), b = it2->imag();
				lli y = (a*a - b*b)/2;
				lli z = (c*c - d*d)/2;
				lli e = y+z, f = y-z;
				if(isSq(e) && isSq(f)){
					cout << "x=" << x << "\n";
					cout << "y=" << y << "\n";
					cout << "z=" << z << "\n";
					cout << "x+y+z=" << x+y+z << "\n";
					return 0;
				}
			}
		}
	}
	return 0;
}