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

#include <bits/extc++.h>
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

int q;
string s;
ordered_set st[256];

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> s >> q;

	forn (i, s.size())
		st[s[i]].insert(i);

	while (q--) {
		int t, l, r, k;
		char c;

		cin >> t;
		if (t == 1) {
			cin >> l >> r >> k;
			l--, r--;

			int f = 0;

			for (c = 'z'; c >= 'a'; c--) {
				k -= (int)st[c].order_of_key(r + 1) - (int)st[c].order_of_key(l);

				if (k <= 0) {
					cout << c << endl;
					f = 1;
					break;
				}

				int j = st[c].order_of_key(r + 1);

				if (j) {
					l = max(l, *st[c].find_by_order(j - 1));
				}
			}

			if (!f)
				cout << '-' << endl;

		} else {
			cin >> k >> c;
			k--;

			st[s[k]].erase(k);
			s[k] = c;
			st[s[k]].insert(k);
		}
	}

	return 0;
}