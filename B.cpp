#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<lli> mods = {3, 4, 5, 7, 11, 13, 17};

lli modularInverse(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(r0 < 0) s0 *= -1;
	if(s0 < 0) s0 += m;
	return s0;
}

lli chinese(vector<lli> & a, vector<lli> & m){
	lli prod = 1, p, ans = 0;
	for(lli & ni : m) prod *= ni;
	for(int i = 0; i < a.size(); ++i){
		p = prod / m[i];
		ans += (a[i] % m[i]) * modularInverse(p, m[i]) % prod * p % prod;
		while(ans >= prod) ans -= prod; while(ans < 0) ans += prod;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t, n, m;
	cin >> t >> n >> m;
	for(int caso = 1; caso <= t; ++caso){
		vector<lli> a;
		for(int p : mods){
			for(int i = 0; i < 18; ++i){
				if(i) cout << " ";
				cout << p;
			}
			cout << endl;
			int sum = 0;
			for(int i = 0; i < 18; ++i){
				int ai;
				cin >> ai;
				sum += ai;
			}
			a.push_back(sum % p);
		}
		cout << chinese(a, mods) << endl;
		int ok;
		cin >> ok;
		if(ok == -1){
			return 0;
		}
	}
	return 0;
}