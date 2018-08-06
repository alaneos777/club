#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(lli i=0;i<n;i++)
#define pii pair<lli,lli>
#define fi first
#define se second

using namespace std;

const int inf = 1e9;
const int MAXN = 5000001;

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

const lli p = 1 + 2016 * 2017;
const lli orden = 1161216;

lli coef[MAXN];
lli roots[MAXN];
lli inversos[MAXN];


lli power(lli a, lli b) {
	lli ans = 1;
	while(b) {
		if(b & 1) ans = (ans * a) % p;
		a = (a * a) % p;
		b /= 2ll;
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	srand(time(0));

	lli g = 5ll;
	roots[0] = 1;
	forn(i, p) {
		if(i) {
			roots[i] = (roots[i - 1] * g) % p;
			lli x, y;
			lli g = gcd(roots[i] - 1, p, x, y);
			inversos[i] = x;
		}
	}

	lli n;
	cin>>n;

	lli ans = 0;
	forn(i, n) {
		cin>>coef[i];
		if(i % (p - 1) == 0) ans = (ans + coef[i] * n % p) % p;
		else ans = (ans + (coef[i] * (roots[(i * n) % (p - 1)] - 1)) % p * inversos[i] % p) % p;
	}
	if(ans < 0) ans += p;
	cout<<ans<<endl;
	return 0;
}
