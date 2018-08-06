#include <bits/stdc++.h>
 
using namespace std;
 
#define endl '\n'
#define fi first
#define se second
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define FOR(i,n) for (int i = 0; i < n; i++)

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;

int mod = 1e9+7, n;
ll p[100005], q[100005];

ll pot (ll b, int p, int m) {
    ll res = 1;
    b %= m;

    while (p) {
        if (p & 1) {
            res *= b;
            res %= m;
        }

        b *= b;
        b %= m;
        p /= 2;
    }

    return res;
}

ll inv (ll n) {
    return pot(n, mod-2, mod);
}

ii e, f;

int obtRes () {
    f.fi = 1;
    f.se = (q[0] * inv(p[0])) % mod;

    e = f;

    for (int i = 1; i < n; i++) {
        ll k = MOD((q[i] - p[i]) * inv(q[i]), mod);
        ll d = inv(MOD(1 - k * f.fi, mod));

        e = ii( MOD(((p[i] * inv(q[i])) % mod) * d, mod), MOD((1 + (k * f.se) % mod ) *  d, mod));

        f = ii((e.fi * f.fi) % mod, (f.fi * e.se + f.se) % mod);
    }

    return MOD(f.se, mod);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> p[i] >> q[i];

    cout << obtRes() << endl;

	return 0;
}
