#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
using comp = complex<lli>;

const lli M = 1e8;

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

const auto lp = lpSieve(M);

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

auto fact_sq(int n, bool & valid){
	vector<pair<int, int>> f;
	while(n > 1){
		int p = lp[n], e = 0;
		while(n % p == 0){
			n /= p;
			e += 2;
		}
		f.emplace_back(p, e);
		valid &= p % 4 == 1;
	}
	return f;
}

vector<comp> base(M+1);

comp power(comp a, lli b){
	comp ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

int main(){
	for(int p = 5; p <= M; p += 4){
		if(lp[p] == p){
			base[p] = sq2(p);
		}
	}
	int64_t yes = 0, no = 0;
	for(lli c = 5; c <= M; c += 4){
		bool valid = true;
		auto f = fact_sq(c, valid);
		if(!valid) continue;
		vector<comp> bases;
		for(const auto & par : f){
			int p, e;
			tie(p, e) = par;
			bases.push_back(power(base[p], e));
		}
		for(int mask = 0; mask < (1 << (bases.size() - 1)); ++mask){
			comp comb = 1;
			for(int i = 0; i < bases.size(); ++i){
				if(mask & (1 << i)){
					comb *= bases[i];
				}else{
					comb *= conj(bases[i]);
				}
			}
			__int128 m = abs(comb.real()), n = abs(comb.imag());
			if(m < n) swap(m, n);
			__int128 a = m*m - n*n, b = 2*m*n;
			__int128 area = a*b/2;
			//cout << a << " " << b << " " << c*c << "\n";
			if(area % 84 == 0){
				yes++;
			}else{
				no++;
			}
		}
		//cout << "\n";
	}
	cout << no << " " << yes << "\n";
	return 0;
}