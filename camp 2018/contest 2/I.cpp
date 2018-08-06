#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define pii pair<int,int>
#define fi first
#define se second
#define vi vector<pii>
#define pb(a) push_back(a)
#define mod 2007

using namespace std;

const int inf = 1e9;
const int MAXN = 10001;

lli g[MAXN];
lli F[MAXN];
vector<int> divi[MAXN];

void pre(lli N) {
	for(lli i=1;i<=N;i++) {
		lli root = sqrt(i);
		for(lli j=1;j<=root;j++) {
			if(i % j == 0) {
				divi[i].pb(j);
				lli otro = i / j;
				if(otro != j) divi[i].pb(otro);
			}
		}
	}
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
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	pre(MAXN - 1);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>F[i];

	lli inverso, y;
	gcd(F[1], mod, inverso, y);

	g[1] = inverso;
	if(g[1] < 0) g[1] += mod;

	inverso *= -1;

	for(int i=2;i<=n;i++) {
		int ans = 0;
		forn(j, divi[i].size()) {
			int d = divi[i][j];
			if(d == i) continue;
			ans = (ans + g[d] * F[i / d] % mod) % mod;
		}
		ans *= inverso;
		if(ans < 0) ans += mod;
		g[i] = ans;
	}

	forn(i, n)
		cout<<g[i + 1]<<" ";
	cout<<endl;
	return 0;
}
