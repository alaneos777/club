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
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int MX = 205;
ll n, s, k, a[MX];
bitset<200010> dp[65];

void solve () {
	cin >> n >> s >> k;
	forn (i, k) cin >> a[i];

	if (s == 0) {
		cout << (a[0] == 0) << endl;
		return;
	}

	dp[0][0] = 1;

	int i = 0;
	while ((1ll << i) <= s) {
		if (n & (1ll << i)) {
			dp[i + 1].reset();
			forn (j, k)
				dp[i + 1] ^= dp[i] << a[j];
		} else {
			dp[i + 1] = dp[i];
		}

		forn (j, 100001) {
			bool aux = dp[i + 1][2 * j + bool(s & (1ll << i))];
			dp[i + 1][2 * j] = dp[i + 1][2 * j + 1] = 0;
			dp[i + 1][j] = aux;
		}

		i++;
	}

	cout << dp[i][0] << endl;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	int t;
	cin >> t;
	while (t--)
		solve();

	return 0;
}