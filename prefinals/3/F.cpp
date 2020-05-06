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

const int MX = 100005;
int n, r = -1;
ll a[MX], c, y, mx, res, off;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n >> c >> y;
	c--;

	forn (i, n) {
		cin >> a[i];
		if (i != c) {
			mx = max(mx, a[i]);
			if (r != -1 && r != a[i] % (y + 1)) {
				cout << "impossible" << endl;
				return 0;
			}
			r = a[i] % (y + 1);
		}
	}

	forn (i, n)
		if (i != c)
			off += (mx - a[i]) / (y + 1);

	cout << mx << " " << (a[c] - off) + (mx - off) * y << endl;

	return 0;
}
