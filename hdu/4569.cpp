#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

lli eval(const vector<lli> & poly, lli x0, lli p){
	lli ans = 0;
	for(int i = (int)poly.size() - 1; i >= 0; --i){
		ans = (ans * x0 + poly[i]) % p;
	}
	return ans;
}

lli find(const vector<lli> & poly, lli p){
	for(lli x0 = 0; x0 < p; ++x0){
		if(eval(poly, x0, p) == 0) return x0;
	}
	return -1;
}

vector<lli> derivative(const vector<lli> & c){
	vector<lli> ans;
	for(int i = 1; i < c.size(); ++i){
		ans.push_back(i * c[i]);
	}
	return ans;
}

vector<lli> clean(const vector<lli> & c, lli p){
	auto poly = c;
	for(lli & ai : poly){
		ai %= p;
		if(ai < 0) ai += p;
	}
	while(!poly.empty() && poly.back() == 0){
		poly.pop_back();
	}
	return poly;
}

lli inverse(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += m;
	return s0;
}

pair<lli, lli> linear(lli a, lli b, lli m){
	if(a == 0 && b == 0){
		return {0, 1};
	}
	lli g = __gcd(a, b);
	a /= g, b /= g, m /= __gcd(m, g);
	if(__gcd(a, m) != 1) return {-1, 1};
	return {inverse(a, m) * b % m, m};
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	for(int caso = 1; caso <= t; ++caso){
		int deg;
		cin >> deg;
		vector<lli> poly(deg+1);
		for(lli & ai : poly){
			cin >> ai;
		}
		reverse(poly.begin(), poly.end());
		lli p;
		cin >> p;
		auto poly_p = clean(poly, p);
		auto poly_p2 = clean(poly, p*p);
		auto poly_p2_d = clean(derivative(poly), p*p);
		cout << "Case #" << caso << ": ";
		lli x1 = find(poly_p, p);
		if(x1 == -1){
			cout << "No solution!\n";
		}else{
			auto sol = linear(p * eval(poly_p2_d, x1, p*p), eval(poly_p2, x1, p*p), p*p);
			if(sol.first == -1){
				cout << "No solution!\n";
			}else{
				lli x2 = (x1 - sol.first * p) % (p*p);
				if(x2 < 0) x2 += p*p;
				cout << x2 << "\n";
			}
		}
	}
	return 0;
}