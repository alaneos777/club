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
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int MX = 105;
int n, m, a[MX], vis[MX], mem[MX][2 * MX * MX + 5], x, y;
vi adj[MX], b;

void dfs (int u, int c) {
	vis[u] = 1;
	
	if (c) x += a[u];
	else y += a[u];
	
	for (int v : adj[u])
		if (!vis[v])
			dfs(v, 1 - c);
}

int dp (int i, int d) {
	if (i == b.size()) return abs(d - MX * MX);
	
	int &res = mem[i][d];
	if (res != -1) return res;
	
	return res = min(
		dp(i + 1, d - b[i]),
		dp(i + 1, d + b[i])
	);
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	
	while (m--) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	} 
	
	for (int i = 1; i <= n; i++)
		if (!vis[i]) {
			x = y = 0;
			dfs(i, 0);
			b.pb(x - y);
		}
	
	memset(mem, -1, sizeof(mem));
	cout << dp(0, MX * MX) << endl;
			
	return 0;
}