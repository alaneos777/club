#include <bits/stdc++.h>
//#define endl '\n'
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

int par, imp, act, l;

void res (int i, int j) {
    cout << i / 90 << " " << j << endl;
}

int main () {
    //ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    while (1) {
        char c;
        cin >> c;

        if (c == 'W') break;

        if (c == 'J') {
            if (imp < 2 && (l || imp == 0 || par < 3)) {
                res(180, act + 1);
                act += 3;
                imp++;
            } else {
                res(180, 1);
            }
        }

        if (c == 'L') {
            if (imp < 2 && (l || imp == 0 || par < 3)) {
                res(180, act + 1);
                act += 3;
                imp++;
            } else {
                res(0, 1);
            }
        }

        if (c == 'I') {
            if (imp < 2) {
                res(90, act + 1);
                act += 1;
                imp++;
                l = 1;
            } else {
                res(0, 1);
            }
        }

        if (c == 'Z') {
            if (par < 3) {
                res(90, act + 1);
                act += 2;
                par++;
            } else {
                res(180, 1);
            }
        }

        if (c == 'S') {
            if (par < 3) {
                res(90, act + 1);
                act += 2;
                par++;
            } else {
                res(0, 1);
            }
        }

        if (c == 'O') {
            if (par < 3) {
                res(0, act + 1);
                act += 2;
                par++;
            } else {
                res(0, 1);
            }
        }

        if (c == 'T') {
            if (par < 3) {
                res(90, act + 1);
                act += 2;
                par++;
            } else {
                res(180, 1);
            }
        }
    }

    return 0;
}
