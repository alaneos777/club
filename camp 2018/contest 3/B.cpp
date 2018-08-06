#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define pii pair<int,int>
#define fi first
#define se second
#define mod 998244353

using namespace std;

const int inf = 1e9;
const int MAXN = 1000001;

lli inv[MAXN];
lli pot[MAXN];
lli fact[MAXN];

lli power(lli a, lli b) {
	lli ans = 1;
	while(b) {
		if(b & 1) ans = (ans * a) % mod;
		a = (a * a) % mod;
		b /= 2ll;
	}
	return ans;
}

lli go(lli n, lli k) {
	lli s = ((k & 1) ? -1 : 1);
	return (s * (fact[n] * inv[k]) % mod * pot[ n - k ]) % mod;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n;
	cin>>n;
	fact[0] = pot[0] = 1;
	forn(i, MAXN)
		if(i) {
			fact[i] = (fact[i - 1] * (lli) i) % mod;
			pot[i] = (pot[i - 1] * 2ll) % mod;
		}
	forn(i, MAXN)
		inv[i] = power(fact[i], mod - 2);
	
	lli ans = 0;
	forn(i, n + 1)
		ans = (ans + go(n, i) + mod) % mod;
	cout<<ans<<endl;
	return 0;
}
