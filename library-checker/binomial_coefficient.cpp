#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

auto factorice(int n){
	vector<pair<int, int>> f;
	for(int p = 2; p*p <= n; ++p){
		int a = 0;
		while(n % p == 0){
			n /= p;
			a++;
		}
		if(a) f.emplace_back(p, a);
	}
	if(n > 1) f.emplace_back(n, 1);
	return f;
}

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
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

tuple<lli, lli, lli> extgcd(lli a, lli b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		auto[d, x, y] = extgcd(b, a%b);
		return {d, y, x - y*(a/b)};
	}
}

lli inv(lli a, lli m){
	auto[d, x, _] = extgcd(a, m);
	assert(d == 1);
	if(x < 0) x += m;
	assert(a * x % m == 1);
	return x;
}

lli pot(lli n, lli p){
	lli ans = 0;
	while(n /= p) ans += n;
	return ans;
}

pair<lli, lli> crt(const vector<lli>& a, const vector<lli>& m){
	lli x = a[0], mod = m[0];
	for(int i = 1; i < a.size(); ++i){
		auto[d, s, t] = extgcd(mod, -m[i]);
		if((a[i] - x) % d != 0) return {-1, -1};
		lli step = m[i] / d;
		lli k = s * (((a[i] - x) / d) % step) % step;
		if(k < 0) k += step;
		x += mod*k;
		mod *= step;
	}
	return {x, mod};
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t, m;
	cin >> t >> m;
	auto fact = factorice(m);
	vector<lli> rhs;
	for(auto[p, a] : fact){
		rhs.push_back(power(p, a));
	}
	int sz = fact.size();
	vector<vector<int>> pre(sz, vector<int>(m, 1));
	for(int i = 0; i < sz; ++i){
		auto[p, a] = fact[i];
		int pa = rhs[i];
		for(lli j = 2; j < pa; ++j){
			if(j % p == 0) pre[i][j] = pre[i][j-1];
			else pre[i][j] = pre[i][j-1] * j % pa;
		}
	}
	vector<lli> lhs(sz);

	auto factmod = [&](lli n, int idx){
		lli ans = 1;
		auto[p, a] = fact[idx];
		int pa = rhs[idx];
		while(n > 1){
			lli q = n / pa, r = n % pa;
			ans = ans * (q % 2 == 1 && !(p == 2 && a >= 3) ? pa-1 : 1) % pa;
			ans = ans * pre[idx][r] % pa;
			n /= p;
		}
		return ans;
	};

	while(t--){
		lli n, k;
		cin >> n >> k;
		if(m == 1){
			cout << "0\n";
			continue;
		}
		for(int i = 0; i < sz; ++i){
			auto[p, a] = fact[i];
			int pa = rhs[i];
			lli s = pot(n, p) - pot(k, p) - pot(n-k, p);
			lli x = factmod(n, i) * inv(factmod(k, i), pa) % pa * inv(factmod(n-k, i), pa) % pa;
			lhs[i] = powerMod(p, s, pa) * x % pa;
		}
		cout << crt(lhs, rhs).first << "\n";
	}
	return 0;
}