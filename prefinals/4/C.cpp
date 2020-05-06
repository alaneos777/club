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

const int MX = 1e5;

string s;
unordered_map /*map*/<ll, ld> mem[40];

#define isSet(n,j) bool((n) & (1ll << (j)))

ll to_hash (string &s) {
	ll res = 0;
	forn (i, s.size())
		res |= (ll(s[i] == ')')) << i;
	return res;
}

inline bool valid (ll s, int sz) {
	ll x = 0;
	forn (i, sz) {
		x += 1 - 2 * int(isSet(s, i));
		if (x < 0) return 0;
	}
	return x == 0;
}

inline ll del (ll s, int a, int sz) {
	ll mk = (1ll << sz) - 1;
	ll seg = mk ^ ((1ll << a) - 1);
	ll x = s & seg;
	s &= ~seg;
	x &= ~(1ll << a);
	s |= x >> 1;
	s &= (1ll << (sz - 1)) - 1;
	return s;
}

ld dp (ll s, int j) {
	if (!valid(s, j)) return 0;
	if (!j) return 1;

	if (!mem[j].count(s)) {
		ld res = 0;
		int cn = 0;

		for (int a = 0; a < j; a++)
			if (!isSet(s, a)) {
				for (int b = a + 1; b < j; b++)
					if (isSet(s, b)) {
						ll x = s;
						x = del(x, b, j);
						x = del(x, a, j - 1);

						res += dp(x, j - 2);
						cn++;
					}
			}

		cn = max(cn, 1);
		mem[j][s] = res / cn;
	}

	return mem[j][s];
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(20);

	forn (i, 40) {
		mem[i].reserve(1024);
		mem[i].max_load_factor(0.25);
	}

	cin >> s;
	cout << dp(to_hash(s), s.size()) << endl;

	return 0;
}
