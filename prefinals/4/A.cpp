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
typedef double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int MX = 5005, lim = 36000;
int n, dp[MX][MX], sig[MX][MX], a[2 * MX], f[lim + 5], ind = 0;
bitset<MX> bs[MX];
vii res;

struct SW {
	deque<ii> q;

	void insert (int fi, int se) {
		while (q.size() && q.back().fi < fi) q.pop_back();
		q.emplace_back(fi, se);
	} 

	ii query (int se) {
		while (q.size() && a[q.front().se] > se) q.pop_front();
		if (q.size()) return q.front();
		return {0, -1};
	}
};

void rec (int i) {
	if (i == ind + n) return;

	if (bs[ind][i % n]) {
		res.emplace_back(a[i] % lim, a[sig[ind][i % n]] % lim);
		rec(sig[ind][i % n] + 1);
	} else {
		rec(i + 1);
	}
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n;
	forn (i, n) {
		cin >> a[i];
		f[a[i]] = i + 1;
	}

	sort(a, a + n);
	n = unique(a, a + n) - a;

	if (n == 1) {
		cout << 0 << " " << 0 << endl;
		return 0;
	}

	forn (i, n) a[i + n] = a[i] + lim;

	forn (i, n) {
		SW q;

		for (int j = i + n - 1; j >= i; j--) {
			dp[i][j % n] = dp[i][(j + 1) % n];
			sig[i][j % n] = j + 1;

			ii p = q.query(a[j] + lim / 2);

			if (p.se != -1 && p.fi - a[j] > dp[i][j % n]) {
				dp[i][j % n] = p.fi - a[j];
				sig[i][j % n] = p.se;
				bs[i][j % n] = 1;
			}

			q.insert(dp[i][(j + 1) % n] + a[j], j);
		}

		if (dp[i][i] > dp[ind][ind]) ind = i;
	}

	rec(ind);

	cout << dp[ind][ind] << " " << res.size() << endl;
	for (ii r : res) cout << f[r.fi] << " " << f[r.se] << " ";
	cout << endl;

	return 0;
}
