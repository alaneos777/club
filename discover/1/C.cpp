#include <bits/stdc++.h>

#define endl '\n'
#define fi first
#define se second
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb(x) push_back(x)

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int MX = 100005;
int n, x[MX], y[MX], res[MX], mx;
vi adj[MX];

void insert (int u, int k) {
	if (k > x[u]) {
		y[u] = x[u];
		x[u] = k;
	} else if (k > y[u]) {
		y[u] = k;
	}
}

void dfs (int u, int p) {
	for (int v : adj[u])
		if (v != p) {
			dfs(v, u);
			insert(u, x[v] + 1);
		}
}

void dfs (int u, int p, int w) {
	res[u] = max(x[u], w);

	for (int v : adj[u])
		if (v != p) {
			int d = x[v] + 1 == x[u] ? y[u] : x[u];
			dfs(v, u, max(w, d) + 1);
		}
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> n;
	forn (i, n - 1) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}

	dfs(1, 1);
	dfs(1, 1, 0);

	for (int i = 1; i <= n; i++)
		cout << res[i] << " \n"[i == n];

	return 0;
}