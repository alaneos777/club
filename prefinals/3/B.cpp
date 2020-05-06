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

int n, m, r, s, tot, vis[30][30][30 * 30 * 10], mx = 0, mn = 1e9;
char c[30][30];
ld mem[30][30][30 * 30 * 10], res = 1e18;

#define sq(n) ((n)*(n))

ld dp (int i, int j, int s) {
	if (s < 0) return 1e18;
	if (i == mx) return 0;

	ld &res = mem[i][j][s];
	if (vis[i][j][s]) return res;
	vis[i][j][s] = 1;
	res = 1e18;

	for (int x = max(i - r, 0); x <= min(i + r, n - 1); x++)
		for (int y = max(j - r, 0); y <= min(j + r, m - 1); y++)
			if (c[x][y] != '.' && sq(x - i) + sq(y - j) <= sq(r))
				res = min(res, dp(x, y, s - (c[x][y] - '0')) + hypot(x - i, y - j));

	return res;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	cin >> n >> m >> r >> s;

	forn (i, n) forn (j, m) {
		cin >> c[i][j];
		if (c[i][j] != '.') {
			tot += c[i][j] - '0';
			mx = max(mx, i);
			mn = min(mn, i);
		}
	}

	forn (j, m) if (c[mn][j] != '.') res = min(res, dp(mn, j, min(tot, s) - (c[mn][j] - '0')));

	if (res == 1e18) cout << -1 << endl;
	else cout << res << endl;

	return 0;
}
