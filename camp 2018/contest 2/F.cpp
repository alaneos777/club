#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define pii pair<lli, lli>
#define fi first
#define se second
#define pb(a) push_back(a)

using namespace std;

const int inf = 1e9;
const int MAXN = 1000001;

vector<pii> fact(lli n) {
	vector<pii> f;
	int cont = 0;
	while(n % 2 == 0) cont++, n /= 2;
	if(cont > 0) f.pb(pii(2, cont));
	for(lli i=3;i*i<=n;i+=2) {
		cont = 0;
		while(n % i == 0) cont++, n/= i;
		if(cont > 0) f.pb(pii(i, cont));
	}

	if(n > 1) f.pb(pii(n, 1));
	return f;
}

lli power(lli a, lli b) {
	lli ans = 1;
	while(b) {
		if(b & 1) ans = (ans * a);
		a = (a * a);
		b >>= 1;
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n;
	cin>>n;

	vector<pii> f = fact(n);

	lli phi = n, tao = 1, sigma = 1;
	forn(i, f.size()) {
		int p = f[i].fi;
		int q = f[i].se;

		phi -= phi / p;
		tao *= (q + 1);
		sigma *= (power(p, q + 1) - 1) / (p - 1);
	}

	cout<<phi<<" "<<tao<<" "<<sigma<<endl;
	return 0; 
}
