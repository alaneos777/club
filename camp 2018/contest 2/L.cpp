#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define pii pair<int,int>
#define fi first
#define se second
#define vi vector<lli>
#define pb(a) push_back(a)

using namespace std;

const int inf = 1e9;
const int MAXN = 1000001;

vi fact(lli n) {
	vi f;
	int cont = 0;
	while(n % 2 == 0) f.pb(2), n /= 2ll;
	for(lli i=3;i*i<=n;i+=2) {
		cont = 0;
		while(n % i == 0) f.pb(i), n /= i;
	}

	if(n > 1) f.pb(n);
	return f;
}

lli gcd(lli a,lli b,lli &x,lli &y) {
	lli xx = y = 0;
	lli yy = x = 1;
	while(b) {
		lli q = a / b;
		lli t = b; b = a % b; a = t;
		t = xx; xx = x - q * xx; x = t;
		t = yy; yy = y - q * yy; y = t;
	}
	return a;
}

lli power(lli a, lli b, lli mod) {
	lli ans = 1ll;
	while(b) {
		if(b & 1) ans = (ans * a) % mod;
		a = (a * a) % mod;
		b /= 2ll;
	}
	return ans; 
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n,e,c;
	cin>>n>>e>>c;

	vi f = fact(n);
	lli mod = (f[0] - 1ll) * (f[1] - 1ll);
	lli x, y;
	lli g = gcd(e, mod, x, y);
	if(x < 0) x += mod;
	lli d = x;

	cout<<power(c, d, n)<<endl;
	return 0;
}
