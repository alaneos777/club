#include <bits/stdc++.h>
using namespace std;
typedef long long int ull;

ull p = 1e9 + 7;

ull inv(ull a, ull n){
	ull r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si, t0 = 0, t1 = 1, ti, q;
	while(r1 != 0){
		q = r0 / r1;
		ri = r0 % r1, r0 = r1, r1 = ri;
		si = s0 - s1 * q, s0 = s1, s1 = si;
		ti = t0 - t1 * q, t0 = t1, t1 = ti;
	}
	return s0;
}

int main(){
	ios_base::sync_with_stdio(0);
	int n, q, t, l, r, pos;
	ull a, b, x;
	cin >> n >> a >> b >> q;
	ull x0 = - (b * inv(a, p)) % p;
	vector<ull> c(n);
	for(int i = 0; i < n; ++i){
		cin >> c[i];
	}
	for(int a = 0; a < q; ++a){
		cin >> t;
		if(t == 1){
			cin >> pos >> x;
			c[pos] = x;
		}else if(t == 2){
			cin >> l >> r;
			ull res = 0;
			for(int i = r; i >= l; --i){
				res = ((res * x0) % p + c[i]) % p;
			}
			if(res == 0){
				cout << "Yes\n";
			}else{
				cout << "No\n";
			}
		}
	}
	return 0;
}