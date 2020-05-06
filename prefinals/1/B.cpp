#include <bits/stdc++.h>
#define endl '\n'
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < (n); i++)
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

const int MX = (1 << 14) + 5;
int n;
ll a[MX], dp[MX][16];

#define sq(n) ((n)*(n))

void solve (int i, int j, int lvl) {
    if (i == j) {
        dp[i][lvl] = 0;
        return;
    }

    int m = (i + j) / 2;
    solve(i, m, lvl + 1);
    solve(m + 1, j, lvl + 1);

    for (int k = i; k <= m; k++)
        for (int l = m + 1; l <= j; l++) {
            dp[k][lvl] = min(dp[k][lvl], dp[k][lvl + 1] + dp[l][lvl + 1] + (a[k] < a[l] ? sq(a[k] - a[l]) : 0));
            dp[l][lvl] = min(dp[l][lvl], dp[l][lvl + 1] + dp[k][lvl + 1] + (a[k] > a[l] ? sq(a[l] - a[k]) : 0));
        }
}

int main () {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> n;
    forn (i, 1 << n) {
        cin >> a[i + 1];
        fill(dp[i + 1], dp[i + 1] + 16, numeric_limits<ll>::max());
    }
    solve(1, 1 << n, 0);
    cout << dp[1][0] << endl;

    return 0;
}
