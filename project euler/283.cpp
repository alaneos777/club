#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int lim = 1000;

vector<int> sieve(int n){
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

const int M = 3e7;
const auto lp = sieve(M);

void fact(int n, map<int, int> & f, int m){
	assert(n <= M);
	while(n > 1){
		int p = lp[n];
		int cnt = 0;
		while(n % p == 0){
			n /= p;
			cnt++;
		}
		f[p] += cnt * m;
	}
}

vector<lli> divs(const map<int, int> & f){
	vector<lli> ans;
	function<void(lli, map<int, int>::const_iterator)> rec = [&](lli acum, map<int, int>::const_iterator it){
		if(it == f.end()){
			ans.push_back(acum);
		}else{
			lli p_pw = 1;
			lli p; int a;
			tie(p, a) = *it;
			auto it2 = it; ++it2;
			for(int i = 0; i <= a; ++i){
				rec(acum * p_pw, it2);
				p_pw *= p;
			}
		}
	};
	rec(1, f.begin());
	sort(ans.begin(), ans.end());
	return ans;
}

lli solve(int m){
	lli ans = 0;
	map<int, int> f;
	f[2] = 2;
	fact(m, f, 2);
	map<int, int> d;
	fact(2*m, d, 1);
	for(int u : divs(d)){
		for(int v = 1; v*v <= 3*u*u; ++v){
			if(__gcd(u, v) != 1) continue;
			auto f2 = f;
			fact(u*u + v*v, f2, 1);
			lli lim = (lli)4*m*m*(u*u + v*v);
			for(lli d1 : divs(f2)){
				lli d2 = lim / d1;
				if(d1 > d2) break;
				if(d1 >= 2*m/u*(v*v-u*u) && (d1 + 2*m*u) % v == 0 && (d2 + 2*m*u) % v == 0){
					lli a = (d1 + 2*m*u) / v + 2*m*v / u;
					lli b = (d2 + 2*m*u) / v + 2*m*v / u;
					lli c = (d1 + d2 + 4*m*u) / v;
					ans += a+b+c;
				}
			}
		}
	}
	return ans;
}

int main(){
	lli ans = 0;
	for(int r = 1; r <= lim; ++r){
		ans += solve(r);
	}
	cout << ans << "\n";
	return 0;
}