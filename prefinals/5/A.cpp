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

bool add (vi &b, ll x) {
	int m = b.size();

	for (int i = m - 1; i >= 0; i--)
		if (x & (1ll << i))
			x ^= b[i];

	if (!x) return 0;

	for (int i = m - 1; i >= 0; i--)
		if (!b[i] && (x & (1ll << i))) {
			b[i] = x;

			for (int j = i + 1; j < m; j++)
				if (b[j] & (1ll << i))
					b[j] ^= x;

			break;
		}

	return 1;
}

void solve () {
	int n, m;
	ll res = 0;

	cin >> n >> m;

	vi a(62, 0);
	forn (i, n) {
		ll x, y;
		cin >> x >> y;
		res ^= x;
		add(a, x ^ y);
	}

	vi b(62, 0);
	forn (i, m) {
		ll x, y;
		cin >> x >> y;
		res ^= x;
		add(b, x ^ y);
	}

	for (int i = 61; i >= 0; i--) {
		if (res & (1ll << i)) {
			if (!a[i] && b[i]) {
				res ^= b[i];
			} else if (a[i] && b[i]) {
				res ^= b[i];
				add(a, a[i] ^ b[i]);
			}
		} else {
			if (a[i] && !b[i]) {
				res ^= a[i];
			} else if (a[i] && b[i]) {
				add(a, a[i] ^ b[i]);
			}
		}
	}

	cout << res << endl;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int t;
	cin >> t;
	while (t--)
		solve();

	return 0;
}
