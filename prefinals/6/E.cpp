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

const int MX = 4005, inf = 1e9;

struct ST {
	int st[4 * MX], lz[4 * MX];

	ST () {
		fill(st, st + 4 * MX, -inf);
		memset(lz, 0, sizeof(lz));
	}

	void push (int i, int j, int pos) {
		if (i < j) {
			lz[pos * 2] += lz[pos];
			lz[pos * 2 + 1] += lz[pos];
		}
		st[pos] += lz[pos];
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

	void assign (int i, int j, int pos, int x, int k) {
		push(i, j, pos);

		if (x < i || j < x) return;
		if (i == j) {
			st[pos] = k;
			return;
		}

		int m = (i + j) / 2;
		assign(i, m, pos * 2, x, k);
		assign(m + 1, j, pos * 2 + 1, x, k);
		st[pos] = max(st[pos * 2], st[pos * 2 + 1]);
	}

	int query (int i, int j, int pos, int a, int b) {
		push(i, j, pos);

		if (b < i || j < a) return -inf;
		if (a <= i && j <= b) return st[pos];

		int m = (i + j) / 2;
		return max(
			query(i, m, pos * 2, a, b),
			query(m + 1, j, pos * 2 + 1, a, b)
		);
	}
}dp[MX];

int n, res[MX], mx[MX];
ii a[MX];
vi c = {inf};

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n;
	forn (i, n) {
		cin >> a[i].fi >> a[i].se;
		c.pb(a[i].fi);
		c.pb(a[i].se);
	}

	sort(all(c));
	c.erase(unique(all(c)), c.end());

	forn (i, n) {
		a[i].fi = upper_bound(all(c), a[i].fi) - c.begin();
		a[i].se = upper_bound(all(c), a[i].se) - c.begin();
	}

	sort(a, a + n);

	int sz = c.size();
	for (int i = 1; i <= sz; i++)
		dp[0].assign(1, sz, 1, i, 0);

	for (int i = 1; i <= n; i++) {
		fill(mx, mx + MX, -inf);

		for (int j = n - 1; j >= 0; j--) {
			int x, y;
			tie(x, y) = a[j];

			dp[i - 1].update(1, sz, 1, y + 1, sz, 1);
			int mx = dp[i - 1].query(1, sz, 1, y + 1, sz);
 
			if (mx > 0)
				dp[i].assign(1, sz, 1, x, mx);
		}

		int m = dp[i].query(1, sz, 1, 1, sz);
		//if (i > m) break;

		for (int j = i; j <= m; j++)
			res[j] = i;
	}

	for (int i = n; i > 0; i--)
		cout << res[i] << " ";
	cout << endl;

	return 0;
}
