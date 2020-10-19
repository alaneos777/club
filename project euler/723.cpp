#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;
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

struct comparer{
	bool operator() (const comp & a, const comp & b) const{
		return a.real() < b.real() || (a.real() == b.real() && a.imag() < b.imag());
	}
};

set<comp, comparer> sq2(const vector<pair<int, int>> & f){
	set<comp, comparer> s;
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

lli half(const comp & p){
	return p.imag() < 0 || (p.imag() == 0 && p.real() < 0);
}

struct comparer2{
	bool operator() (const comp & a, const comp & b) const{
		return make_pair(half(a), lli(0)) < make_pair(half(b), (conj(a)*b).imag());
	}
};

int64_t f(const vector<pair<int, int>> & f){
	auto s = sq2(f);
	vector<comp> p(s.begin(), s.end());
	int n = p.size();
	sort(p.begin(), p.end(), comparer2());
	int64_t ans = 0;

	for(int i = 0; i < n; ++i){
		comp c = -p[i];
		int k = lower_bound(p.begin() + i+1, p.end(), c, comparer2()) - p.begin();
		if(k != n && p[k] == c){
			ans += int64_t(k - i - 1) * (n - 1 - k);
		}
	}

	for(int j = 0; j < n; ++j){
		comp d = -p[j];
		int l = lower_bound(p.begin() + j+1, p.end(), d, comparer2()) - p.begin();
		if(l != n && p[l] == d){
			ans += j * int64_t(l - j - 1);
		}
	}

	map<comp, vector<pair<int, int>>, comparer> mp;
	for(int i = 0; i < n-1; ++i){
		for(int k = i+1; k < n; ++k){
			mp[p[i] * p[k]].emplace_back(i, k);
		}
	}
	for(const auto & par : mp){
		comp prod = -par.first;
		const vector<pair<int, int>> & lhs = par.second;
		if(mp.count(prod)){
			const vector<pair<int, int>> & rhs = mp[prod];
			for(const auto & ac : lhs){
				int i, k;
				tie(i, k) = ac;
				for(const auto & bd : rhs){
					int j, l;
					tie(j, l) = bd;
					if(i < j && j < k && k < l){
						ans++;
					}
				}
			}
		}
	}

	for(int i = 0; i < n; ++i){
		comp c = -p[i];
		int k = lower_bound(p.begin() + i+1, p.end(), c, comparer2()) - p.begin();
		if(k != n && p[k] == c){
			for(int j = i+1; j < k; ++j){
				comp d = -p[j];
				int l = lower_bound(p.begin() + k+1, p.end(), d, comparer2()) - p.begin();
				if(l != n && p[l] == d){
					ans--;
				}
			}
		}
	}

	for(int i = 0; i < n; ++i){
		comp c = -p[i];
		int k = lower_bound(p.begin() + i+1, p.end(), c, comparer2()) - p.begin();
		if(k != n && p[k] == c){
			if(mp.count(p[i] * p[i])){
				const vector<pair<int, int>> & rhs = mp[p[i] * p[i]];
				for(const auto & bd : rhs){
					int j, l;
					tie(j, l) = bd;
					if(i < j && j < k && k < l){
						ans--;
					}
				}
			}
		}
	}

	for(int j = 0; j < n; ++j){
		comp d = -p[j];
		int l = lower_bound(p.begin() + j+1, p.end(), d, comparer2()) - p.begin();
		if(l != n && p[l] == d){
			if(mp.count(p[j] * p[j])){
				const vector<pair<int, int>> & lhs = mp[p[j] * p[j]];
				for(const auto & ac : lhs){
					int i, k;
					tie(i, k) = ac;
					if(i < j && j < k && k < l){
						ans--;
					}
				}
			}
		}
	}

	comp I(0, 1);
	for(int i = 0; i < n; ++i){
		comp a = p[i], b = a*I, c = -a, d = -a*I;
		int j = lower_bound(p.begin() + i+1, p.end(), b, comparer2()) - p.begin();
		if(j != n && p[j] == b){
			int k = lower_bound(p.begin() + j+1, p.end(), c, comparer2()) - p.begin();
			if(k != n && p[k] == c){
				int l = lower_bound(p.begin() + k+1, p.end(), d, comparer2()) - p.begin();
				if(l != n && p[l] == d){
					ans++;
				}
			}
		}
	}

	return ans;
}

int main(){
	int64_t ans = 0;
	//vector<pair<int, int>> fact = {{5,1},{13,1},{17,1}};
	vector<pair<int, int>> fact = {{5,6}, {13,3}, {17,2}, {29,1}, {37,1}, {41,1}, {53,1}, {61,1}};
	
	int cnt = 0;
	function<void(int)> rec = [&](int idx){
		if(idx == fact.size()){
			ans += f(fact);
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
	cout << ans << "\n";

	return 0;
}