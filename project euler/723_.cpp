#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
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

unordered_map<int, comp> base;

set<pair<lli, lli>> sq2(const vector<pair<int, int>> & f){
	set<pair<lli, lli>> ans;
	vector<vector<comp>> lists;
	for(const auto & par : f){
		int p, e;
		tie(p, e) = par;
		if(e == 0) continue;
		if(p % 4 == 3 && e % 2 == 1) return {};
	}
	for(const auto & par : f){
		int p, e;
		tie(p, e) = par;
		if(e == 0) continue;
		vector<comp> list;
		if(p == 2){
			list.push_back(power({1, 1}, e));
		}else if(p % 4 == 3){
			list.push_back(power({p, 0}, e/2));
		}else{
			comp base_p = base[p];
			for(int i = 0; i <= e; ++i){
				list.push_back(power(base_p, i) * conj(power(base_p, e-i)));
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

using ld = long double;
const ld eps = 1e-9, inf = numeric_limits<ld>::max(), pi = acos(-1);
// For use with integers, just set eps=0 and everything remains the same
bool geq(ld a, ld b){return a-b >= -eps;}     //a >= b
bool leq(ld a, ld b){return b-a >= -eps;}     //a <= b
bool ge(ld a, ld b){return a-b > eps;}        //a > b
bool le(ld a, ld b){return b-a > eps;}        //a < b
bool eq(ld a, ld b){return abs(a-b) <= eps;}  //a == b
bool neq(ld a, ld b){return abs(a-b) > eps;}  //a != b

void polarSort(vector<point> & P){
	sort(P.begin(), P.end(), [&](const point & a, const point & b){
		return point(a.half(), 0) < point(b.half(), a.cross(b));
	});
}

lli f(const vector<pair<int, int>> & f){
	auto tmp = sq2(f);
	lli r = 1;
	for(const auto & par : f){
		for(int i = 1; i <= par.second; ++i){
			r *= par.first;
		}
	}
	set<pair<lli, lli>> s;
	for(const auto & x : tmp){
		lli a, b;
		tie(a, b) = x;
		s.emplace(a, b);
		s.emplace(b, a);
		s.emplace(a, -b);
		s.emplace(-b, a);
		s.emplace(-a, b);
		s.emplace(b, -a);
		s.emplace(-a, -b);
		s.emplace(-b, -a);
	}
	vector<comp> p;
	for(const auto & x : s){
		p.emplace_back(x.first, x.second);
	}
	polarSort(p);
	int n = p.size();
	lli ans = 0;
	
	for(int i = 0; i < n; ++i){
		//
	}

	return ans;
}

lli P(lli n){
	if(n & 1){
		return (32*n*n*n - 48*n*n + 25*n - 6) / 3;
	}else{
		return (32*n*n*n - 48*n*n + 25*n) / 3;
	}
}

lli f_fast(const vector<pair<int, int>> & f){
	lli divs = 1;
	for(auto par : f){
		divs *= par.second + 1;
	}
	return P(divs);
}

int main(){
	int64_t ans = 0;
	//vector<pair<int, int>> fact = {{5,1},{13,1},{17,1}};
	vector<pair<int, int>> fact = {{5,6}, {13,3}, {17,2}, {29,1}, {37,1}, {41,1}, {53,1}, {61,1}};
	for(auto par : fact){
		base[par.first] = sq2(par.first);
	}
	
	/*int cnt = 0;
	function<void(int)> rec = [&](int idx){
		if(idx == fact.size()){
			ans += f_fast(fact);
			cout << cnt++ << "\n";
		}else{
			int e = fact[idx].second;
			fact[idx].second = 0;
			for(int i = 0; i <= e; ++i){
				rec(idx+1);
				fact[idx].second++;
			}
			fact[idx].second = e;
		}
	};
	rec(0);
	cout << ans << "\n";*/

	cout << "Solve[{";
	for(int i = 0; i <= 7; ++i){
		for(int j = 0; j <= 7; ++j){
			if(i % 2 == 1 && j % 2 == 1){
				cout << "P[" << i << ", " << j << "]==" << f({{5, i}, {13, j}}) << ",";
			}
		}
	}
	cout << "},{a,b,c,d,e,f,g,h,i,j}]";

	return 0;
}