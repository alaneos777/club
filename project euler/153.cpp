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

auto lp = lpSieve(1e8);

auto fact(int n){
	vector<pair<int, int>> f;
	while(n > 1){
		int p = lp[n], a = 0;
		while(n % p == 0){
			n /= p;
			a++;
		}
		f.emplace_back(p, a);
	}
	return f;
}

lli s(int n){
	vector<vector<comp>> lists;
	for(auto[p, a] : fact(n)){
		vector<comp> list;
		if(p == 2){
			int p_pow = 1;
			for(int i = 0; i <= a; ++i){
				list.push_back(p_pow);
				if(i < a) list.push_back(comp{p_pow, p_pow});
				p_pow *= p;
			}
		}else if(p % 4 == 3){
			int p_pow = 1;
			for(int i = 0; i <= a; ++i){
				list.push_back(p_pow);
				p_pow *= p;
			}
		}else{
			auto[re, im] = sq2(p);
			comp w = {re, im};
			comp z = {re, -im};
			comp w_pow = 1;
			for(int i = 0; i <= a; ++i){
				comp z_pow = 1;
				for(int j = 0; j <= a; ++j){
					list.push_back(w_pow * z_pow);
					z_pow *= z;
				}
				w_pow *= w;
			}
		}
		lists.push_back(list);
	}
	lli ans = 0;
	function<void(int, comp)> f = [&](int pos, comp z){
		if(pos == lists.size()){
			ans += abs(z.real()) + abs(z.imag());
		}else{
			for(comp x : lists[pos]){
				f(pos+1, z*x);
			}
		}
	};
	f(0, 1);
	return ans;
}

int main(){
	lli sum = 0;
	for(int n = 1; n <= 1e8; ++n){
		sum += s(n);
		if(n % 10000 == 0) cout << n << "\n";
	}
	cout << sum << "\n";
	return 0;
}