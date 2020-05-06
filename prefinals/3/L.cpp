#include <bits/stdc++.h>
#define endl '\n'
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < n; i++)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define pb(x) push_back(x)
#define fi first
#define se second
#define all(v) v.begin(), v.end()
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int MX = 300005, SIG = 26;
int nex[MX][SIG], finish[MX], sz = 1, fin[MX], euler = 1, fail[MX], l[MX], r[MX];
int dp[MX], w[MX], n, res, mp[MX], cn;
string s[MX];
vi adj[MX];

int st[4 * MX], lz[4 * MX];

void clear () {
	forn (i, sz) {
		fail[i] = 0;
		fin[i] = 0;
		adj[i].clear();
		memset(nex[i], 0, sizeof(nex[i]));
	}

	sz = 1;
	euler = 1;
	res = 0;
	cn = 0;
}

void build (int i, int j, int pos) {
	st[pos] = lz[pos] = 0;

	if (i < j) {
		int m = (i + j) / 2;
		build(i, m, pos * 2);
		build(m + 1, j, pos * 2 + 1);
	}
}

void push (int i, int j, int pos) {
	if (i < j) {
		lz[pos * 2] = max(lz[pos * 2], lz[pos]);
		lz[pos * 2 + 1] = max(lz[pos * 2 + 1], lz[pos]);
	}

	st[pos] = max(st[pos], lz[pos]);
	lz[pos] = 0;
}

void update (int i, int j, int pos, int a, int b, int k) {
	push(i, j, pos);

	if (b < i || j < a) return;
	if (a <= i && j <= b) {
		lz[pos] = k;
		push(i, j, pos);
		return;
	}

	int m = (i + j) / 2;
	update(i, m, pos * 2, a, b, k);
	update(m + 1, j, pos * 2 + 1, a, b, k);

	st[pos] = max(st[pos * 2], st[pos * 2 + 1]);
}

int query (int i, int j, int pos, int x) {
	push(i, j, pos);

	if (i == j) return st[pos];

	int m = (i + j) / 2;
	if (x <= m) return query(i, m, pos * 2, x);
	return query(m + 1, j, pos * 2 + 1, x);
}

int insert (string &s) {
	int u = 0;

	for (char c : s) {
		c -= 'a';

		if (!nex[u][c]) {
			nex[u][c] = sz;
			finish[sz] = -1;
			sz++;
		}

		u = nex[u][c];
	}

	if (!fin[u]) {
		fin[u] = 1;
		finish[u] = cn++;
	}

	return finish[u];
}

int getFail (int u, int c) {
	while (u && !nex[u][c])
		u = fail[u];
	return nex[u][c];
}

void build () {
	queue<int> q;

	for (int i = 0; i < SIG; i++)
		if (nex[0][i])
			q.push(nex[0][i]);

	while (q.size()) {
		int u = q.front();
		q.pop();

		for (int i = 0; i < SIG; i++) {
			int v = nex[u][i];

			if (v) {
				fail[v] = getFail(fail[u], i);
				q.push(v);
			}
		}
	}
}

void dfs (int u) {
	l[u] = euler++;
	for (int v : adj[u])
		dfs(v);
	r[u] = euler - 1;
}

void solve () {
	cin >> n;

	forn (i, n) {
		cin >> s[i] >> w[i];
		mp[i] = insert(s[i]);
		dp[mp[i]] = 0;
	}

	build();
	build(1, sz, 1);

	for (int i = 1; i < sz; i++)
		adj[fail[i]].pb(i);

	dfs(0);

	forn (i, n) {
		int t = mp[i], act = 0, u = 0;

		for (char c : s[i]) {
			c -= 'a';
			u = nex[u][c];
			act = max(act, query(1, sz, 1, l[u]));
		}

		dp[t] = max(dp[t], act + w[i]);
		res = max(res, dp[t]);
		update(1, sz, 1, l[u], r[u], dp[t]);
	}

	cout << res << endl;

	clear();
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	int t;
	cin >> t;
	while (t--)
		solve();

	return 0;
}
