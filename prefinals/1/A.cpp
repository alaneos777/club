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
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int MX = 100005;
int n, m, a[MX], b[MX], x[MX], y[MX], ft[MX];
vi pos[MX], in[MX];
ll res;

void update (int i, int k) {
	while (i < MX) {
		ft[i] = min(ft[i], k);
		i += i & -i;
	}
}

int query (int i) {
	int res = 1e9;
	while (i) {
		res = min(res, ft[i]);
		i -= i & -i;
	}
	return res;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	fill(ft, ft + MX, 1e9);
	
	cin >> n;
	forn (i, n) {
		cin >> a[i] >> b[i];
		pos[a[i]].pb(i);
	}

	cin >> m;
	forn (i, m) {
		cin >> x[i] >> y[i];
		in[x[i]].pb(i);
	}

	for (int j = MX - 1; j; j--) {
		for (int i : pos[j])
			update(b[i], i + 1);

		for (int i : in[j])
			res += query(y[i]);
	}

	cout << res << endl;
	
	return 0;
}