#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli inverse(lli a, lli n){
	lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	assert(r0 == 1);
	if(s0 < 0) s0 += n;
	return s0;
}

auto rec(vector<lli> P, lli n, lli mod){
	for(int i = 0; i < P.size()-1; ++i){
		P[i] = -P[i];
		if(P[i] < 0) P[i] += mod;
	}
	P.pop_back();
	int deg = P.size();
	vector<lli> ans(deg), R(2*deg);
	ans[0] = 1;
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	do{
		int d = (n & p) != 0;
		fill(R.begin(), R.end(), 0);
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++)
				(R[i + j + d] += ans[i] * ans[j]) %= mod;
		for(int i = deg-1; i >= 0; i--)
			for(int j = 0; j < deg; j++)
				(R[i + j] += R[i + deg] * P[j]) %= mod;
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);
	return ans;
}

void clean(vector<lli> & poly){
	while(!poly.empty() && poly.back() == 0) poly.pop_back();
	if(poly.empty()) poly.push_back(0);
}

lli p;

vector<lli> operator/(const vector<lli> & a, const vector<lli> & b){
	vector<lli> r = a;
	while(r.size() >= b.size() && !(r.size() == 1 && r[0] == 0)){
		size_t g = r.size() - b.size();
		lli q = r.back() * inverse(b.back(), p) % p;
		for(int i = 0; i < b.size(); ++i){
			r[i+g] -= b[i] * q % p;
			if(r[i+g] < 0) r[i+g] += p;
		}
		clean(r);
	}
	return r;
}

auto Gcd(vector<lli> a, vector<lli> b){
	clean(a), clean(b);
	while(!(b.size() == 1 && b[0] == 0)){
		vector<lli> r = a / b;
		/*for(lli tt : a) cout << tt << " ";
		cout << " % ";
		for(lli tt : b) cout << tt << " ";
		cout << " = ";
		for(lli tt : r) cout << tt << " ";
		cout << "\n";*/
		a = b, b = r;
	}
	clean(a);
	return a;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	while(cin >> n >> p && p){
		vector<lli> poly(n+1);
		for(lli & pi : poly){
			cin >> pi;
			pi %= p;
			if(pi < 0) pi += p;
		}
		clean(poly);
		if(poly.size() == 1){
			if(poly[0] == 0) cout << p << "\n";
			else cout << "0\n";
			continue;
		}
		for(int i = 0; i < poly.size(); ++i){
			poly[i] = poly[i] * inverse(poly.back(), p) % p;
		}
		/*for(lli x = 0; x < p; ++x){
			lli eval = 0, x_pow = 1;
			for(lli y : poly){
				eval = (eval + y * x_pow) % p;
				x_pow = x_pow * x % p;
			}
			if(eval == 0){
				cout << "!" << x << "\n";
			}
		}*/
		vector<lli> res = rec(poly, p, p);
		if(res.size() <= 1) res.resize(2);
		res[1]--;
		if(res[1] < 0) res[1] += p;
		clean(res);
		vector<lli> ans = Gcd(poly, res);
		//for(lli tt : res) cout << tt << " "; cout << "\n";
		//for(lli tt : ans) cout << tt << " "; cout << "\n";
		cout << ans.size()-1 << "\n";
	}
	return 0;
}