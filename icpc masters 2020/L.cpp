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

const int MX = 105;
int n, mem[MX][MX], a[MX];

int dp (int i, int j) {
	if (i >= j) return 0;
	
	int &res = mem[i][j];
	if (res != -1) return res;
	res = max(dp(i + 1, j), dp(i, j - 1));
	
	for (int k = i + 1; k < j; k++) {
		bool s = __builtin_popcount(a[i] & a[j]) >= 2;
		
		if (s) {
			bool f = dp(i, k) == k - i - 1;
			bool g = dp(k, j) == j - k - 1;	
			
			if (f && g)
				res = max(res, j - i - 1);
		}
		
		res = max(res, dp(i, k) + dp(k, j));
	}
	
	return res;
}

void solve () {
	cin >> n;
	
	forn (i, n) {
		string s;
		cin >> s;
		
		a[i] = 0;
		for (char c : s)
			a[i] |= 1 << (c - 'A');
	}
	
	memset(mem, -1, sizeof(mem));
	cout << dp(0, n - 1) << endl;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	int t;
	cin >> t;
	while (t--)
		solve();
			
	return 0;
}