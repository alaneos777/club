#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define pii pair<int,int>
#define fi first
#define se second

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, t, i;

    cin >> t;
    while (t--) {
        cin >> i;
        //i = t;

        if (i < 6) {
            if (i == 2) cout << "Alice" << endl;
            if (i == 3) cout << "Bob" << endl;
            if (i == 4) cout << "Alice" << endl;
            if (i == 5) cout << "Alice" << endl;
            continue;
        }

        int ans = 0;
        //cout << i << endl;
        for (lli j = 2; j <= 2; j++) {
            lli d = i - j;

            lli h = j * (j-1) / 2;
            lli g = d * (d-1) / 2;
            ans += (h + g) % 2;
            //cout << (h+g)%2 << " ";
        }
        //cout << endl;
        if ((ans > 0)) cout << "Bob" << endl;
        else {
            cout << "Alice" << endl;
            //assert(i % 4 == 1);
        }
    }

    return 0;
}
