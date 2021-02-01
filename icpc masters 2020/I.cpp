#include <bits/stdc++.h>

#define endl '\n'
#define fi first
#define se second
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < int(n); i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb push_back

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int MX = 12;
ll mem[MX][MX][MX][MX][MX], a[4];

ll dp (int a, int b, int c, int d, int f) {
	if (min({a, b, c, d}) < 0) return 0;
	if (max({a, b, c, d}) == 0) return 1;
	
	ll &res = mem[a][b][c][d][f];
	if (res != -1) return res;
	res = 0;
	
	if (f != 0) res += dp(a - 1, b, c, d, 0);
	if (f != 1) res += dp(a, b - 1, c, d, 1);
	if (f != 2) res += dp(a, b, c - 1, d, 2);
	if (f != 3) res += dp(a, b, c, d - 1, 3);
	
	return res;
}

void solve () {
	forn (i, 4) cin >> a[i];
	memset(mem, -1, sizeof(mem));
	cout << dp(a[0], a[1], a[2], a[3], 4) << endl;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	int t;
	cin >> t;
	while (t--)
		solve();
			
	return 0;
}