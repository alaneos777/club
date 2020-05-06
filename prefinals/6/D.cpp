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
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int MX = 1005;
int n, a[MX], to[MX][MX];
set<ii> sw, vis;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n;
	forn (i, n - 1) {
		int x;

		int j = 0;
		while (cin >> x, x) {
			sw.emplace(x, i);
			to[i][x] = j;
			j++;
		}
	}

	int f = 1;
	while (f) {
		f = 0;
		iota(a, a + n, 0);
		vis.clear();

		auto it = sw.begin();

		while (it != sw.end()) {
			ii p(a[it->se], a[it->se + 1]);
			if (p.fi > p.se) swap(p.fi, p.se);

			if (!vis.count(p)) {
				vis.insert(p);
				swap(a[it->se], a[it->se + 1]);
				it++;
				continue;
			}

			auto jt = it;
			jt--;
 
			while (1) {
				ii q(a[jt->se], a[jt->se + 1]);
				if (q.fi > q.se) swap(q.fi, q.se);
				vis.erase(q);
				swap(a[jt->se], a[jt->se + 1]);

				if (p == q) {
					sw.erase(it);
					it = jt;
					it++;
					sw.erase(jt);
					break;
				}

				jt--;
			}

			f = 1;
		}
	}

	cout << sw.size() << endl;
	for (ii res : sw)
		cout << res.se + 1 << " " << to[res.se][res.fi] + 1 << endl;

	return 0;
}
