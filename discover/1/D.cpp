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

const int MX = 100005;
int n, d[MX], mn = MX, mx;
vi pos[MX];

void no () {
	cout << "Epic fail" << endl;
	exit(0);
}

void add (int x, int y) {
	cout << x << " " << y << endl;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> d[i];
		pos[d[i]].pb(i);
		mx = max(mx, d[i]);
		mn = min(mn, d[i]);
	}

	if ((mx + 1) / 2 != mn) no();
	if (pos[mx].size() < 2) no();
	if (mx % 2 == 0 && pos[mn].size() != 1) no();
	if (mx % 2 == 1 && pos[mn].size() != 2) no();

	for (int i = mn + 1; i <= mx; i++)
		if (pos[i].size() < 2)
			no();

	cout << "I got it" << endl;
	if (pos[mn].size() == 2)
		add(pos[mn][0], pos[mn][1]);

	for (int i = mn + 1; i <= mx; i++) {
		add(pos[i][0], pos[i - 1][0]);

		if (pos[i - 1].size() >= 2)
			add(pos[i][1], pos[i - 1][1]);
		else
			add(pos[i][1], pos[i - 1][0]);
	}

	for (int i = mn + 1; i <= mx; i++)
		for (int j = 2; j < pos[i].size(); j++)
			add(pos[i][j], pos[i - 1][0]);

	return 0;
}