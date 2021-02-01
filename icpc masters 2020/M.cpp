#include <bits/stdc++.h>

#define endl '\n'
#define fi first
#define se second
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < int(n); i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb push_back

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int mod = 1000000007;

int n, m, vis[33], f[33];
ll res = 1, fac[33], inv[33];
vi adj[33], gra[33];
vi mem, in;

ll pot (ll b, int p) {
	ll res = 1;
	while (p) {
		if (p & 1) (res *= b) %= mod;
		(b *= b) %= mod;
		p /= 2;
	}
	return res;
}

void dfs (int u) {
	vis[u] = 1;
	in.pb(u);
	for (int v : gra[u])
		if (!vis[v])
			dfs(v);
}

int dp (int mk) {
	if (__builtin_popcount(mk) == m) return 1;
	
	ll res = mem[mk];
	if (res != -1) return res;
	res = 0;
	
	forn (i, m) if (~mk & (1 << i)) {
		int g = 1;
		
		for (int j : adj[in[i]])
			if (~mk & (1 << f[j]))
				g = 0;
		
		if (g)
			res += dp(mk | (1 << i));
	}
	
	return mem[mk] = res % mod;
}

void solve () {
	cin >> n >> m;
	 
	for (int i = 1; i <= n; i++) {
		adj[i].clear();
		gra[i].clear();
		vis[i] = 0;
	}
	
	while (m--) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		
		gra[u].pb(v);
		gra[v].pb(u);
	}
	
	res = fac[n];
	
	for (ll i = 1; i <= n; i++)
		if (!vis[i]) {
			in.clear();
			dfs(i);
			
			m = in.size();
			mem = vi(1 << m, -1);
			
			forn (i, m)
				f[in[i]] = i;
			
			(res *= dp(0)) %= mod;
			(res *= inv[m]) %= mod;
		}
	
	cout << res << endl;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	fac[0] = inv[0] = 1;
	
	for (int i = 1; i < 33; i++) {
		fac[i] = i * fac[i - 1] % mod;
		inv[i] = pot(fac[i], mod - 2);
	}
	
	int t;
	cin >> t;
	while (t--)
		solve();
			
	return 0;
}