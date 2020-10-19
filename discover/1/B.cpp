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
typedef double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int MX = 51;
int n, a, b;
ld p, mem[MX][MX][MX][MX], ex[MX];
char vis[MX][MX][MX][MX];

ld dp (int d, int n, int x, int k) {
	if (k < 0) return 0;
	if (n < x) return 0;
	if (d == 0 || n == 0) return k == 0;

	ld &res = mem[d][n][x][k];
	if (vis[d][n][x][k]) return res;
	vis[d][n][x][k] = 1;
	res = 0;

	res += (1.0l * x / n) * (p * dp(d - 1, n - 1, x - 1, k - 1) + (1 - p) * dp(d - 1, n, x - 1, k - 1));
	res += (1.0l * (n - x) / n) * (p * dp(d - 1, n - 1, x, k) + (1 - p) * dp(d - 1, n, x, k));

	return res;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	cin >> n >> a >> b >> p;

	for (int i = 1; i <= n; i++) {
		ld sum = 0, act = 0;

		for (int d = a; d <= b; d++)
			act += dp(d, n, i, 0);
		act /= b - a + 1;

		for (int j = 0; j < i; j++) {
			ld x = 0;

			for (int d = a; d <= b; d++)
				x += dp(d, n, i, i - j);
			x /= b - a + 1;

			sum += x * ex[j];
		}

		ex[i] = (sum + 1) / (1 - act);
	}

	cout << ex[n] << endl;

	return 0;
}