#include <bits/stdc++.h>

#define endl '\n'
#define fi first
#define se second
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < int(n); i++)
#define forr(i,a,b) for (int i = int(a); i <= int(b); i++)
#define all(v) v.begin(), v.end()
#define pb push_back

using namespace std;

typedef unsigned long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int MX = 1005;
int n, m, vis[MX], cn;
vi adj[MX];
bitset<MX> dp;

void dfs (int u) {
	vis[u] = 1;
	cn++;
	
	for (int v : adj[u])
		if (!vis[v])
			dfs(v);
}

void main_() {
	cin >> n >> m;
	
	forn (kk, m) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
		if (vis[i]) continue;
		
		cn = 0;
		dfs(i);
		
		dp |= dp << cn;
	}
	
	cout << (int)dp.count() - 1 << endl;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	int t = 1;
	// cin >> t;
	while (t--)
		main_();
	
	return 0;
}
