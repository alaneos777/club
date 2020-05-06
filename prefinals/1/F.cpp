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

const int MX = 100005, CN = 3;
const int mod[] = {
    1000000021,
    1000000009,
    998244353
};

int n, m, c, cn[42][MX], res;
ll b[CN][MX], h[CN][42];
map<vi, int> mp;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    forn (i, CN) {
        uniform_int_distribution<> dis(0, mod[i] - 1);
        
        b[i][0] = 1;
        b[i][1] = dis(rng);

        for (int j = 2; j < MX; j++)
            b[i][j] = b[i][1] * b[i][j - 1] % mod[i];
    }

    cin >> n >> m >> c;
    forn (i, n) {
        forn (j, m) {
            int p;
            cin >> p;
            cn[i][p - 1]++;
        }

        forn (k, CN) 
            forn (j, c)
                (h[k][i] += (cn[i][(j + 1) % c] - cn[i][j] + mod[k]) * b[k][j]) %= mod[k];
    }

    if (n <= 20) {
        forn (i, (1 << n)) {
            vi s(CN);

            forn (j, n) if (i & (1 << j)) {
                forn (k, CN) (s[k] += h[k][j]) %= mod[k];
            }

            if (*max_element(all(s)) == 0) res = max(res, __builtin_popcount(i));
        }
    } else {
        forn (i, (1 << 20)) {
            vi s(CN);

            forn (j, 20) if (i & (1 << j)) {
                forn (k, CN) (s[k] += h[k][j]) %= mod[k];
            }

            mp[s] = max(mp[s], __builtin_popcount(i));
        }

        forn (i, (1 << n - 20)) {
            vi s(CN);

            forn (j, n - 20) if (i & (1 << j)) {
                forn (k, CN) (s[k] += -h[k][j + 20] + mod[k]) %= mod[k];
            }

            if (mp.count(s)) res = max(res, mp[s] + __builtin_popcount(i));
        }
    }

    cout << res << endl;

	return 0;
}
